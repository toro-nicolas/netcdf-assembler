/*
** SEAGNAL PROJECT, 2024
** netcdf-assembler
** File description:
** The file containing the variables functions
*/
/**
 * @file variables.cc
 * @brief The file containing the variables functions
 * @author Nicolas TORO
 */

#include "../include/get_values.hh"
#include "../include/set_values.hh"

/**
 * @brief Update the variable size
 * @param in_s_file The file information
 * @param in_s_var The variable to update
 * @return <b>void</b>
 */
void update_variable_size(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    in_s_var.i_data_size = 1;
    for (int32_t i_dim_index = 0; i_dim_index < in_s_var.i_ndims; i_dim_index++) {
        in_s_var.ai_dims_size[i_dim_index] = get_dimension_size(in_s_file, in_s_var.ai_dimids[i_dim_index]);
        in_s_var.i_data_size *= in_s_var.ai_dims_size[i_dim_index];
    }
}

/**
 * @brief Get the end index of a variable
 * @param in_s_file The file information
 * @param in_s_var The variable information
 * @return <b>size_t *</b> The end index
 */
size_t *get_end_variable_start(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    size_t *out_ai_start = (size_t *)calloc(in_s_var.i_ndims, sizeof(size_t));

    for (int32_t i_dim_index = 0; i_dim_index < in_s_var.i_ndims; i_dim_index++)
        out_ai_start[i_dim_index] = in_s_var.ai_dims_size[i_dim_index];
    return out_ai_start;
}

/**
 * @brief Check if the data is in the variable
 * @param in_s_file The file information
 * @param in_s_var The variable to check
 * @param in_data The data to check
 * @return <b>bool</b> <u>True</u> if the data is in the variable, <u>False</u> otherwise
 */
template <typename T>
bool data_is_in_variable(file_information_t & in_s_file, variable_information_t & in_s_var, T in_data)
{
    size_t *ai_start = (size_t *)calloc(in_s_var.i_ndims + 1, sizeof(size_t));

    for (size_t i_index = 0; i_index < in_s_var.i_data_size; i_index++) {
        T value = get_var_value<T>(in_s_file, in_s_var, ai_start);
        if constexpr (std::is_same<T, char *>::value) {
            if (strcmp(in_data, value) == 0) {
                free(ai_start);
                return true;
            }
        } else if (in_data == value) {
            free(ai_start);
            return true;
        }

        for (int i_start_index = 0; i_start_index < in_s_var.i_ndims; i_start_index++) {
            if ((ai_start[i_start_index] + 1 == in_s_var.ai_dims_size[i_start_index] && i_start_index == 0)
            || ai_start[i_start_index] == in_s_var.ai_dims_size[i_start_index]) {
                ai_start[i_start_index] = 0;
                ai_start[i_start_index + 1] += 1;
            } else if (i_start_index == 0) {
                ai_start[i_start_index] += 1;
                break;
            }
        }
    }
    free(ai_start);
    return false;
}

/**
 * @brief Get the index from a value
 * @param in_s_file The file information
 * @param in_s_var The variable information
 * @param in_data The data to get the index from
 * @return <b>size_t *</b> The index of the data
 */
template <typename T>
size_t *get_index_from_value(file_information_t & in_s_file, variable_information_t & in_s_var, T in_data)
{
    size_t *out_ai_start = (size_t *)calloc(in_s_var.i_ndims, sizeof(size_t));
    for (size_t i_index = 0; i_index < in_s_var.i_data_size; i_index++) {
        T value = get_var_value<T>(in_s_file, in_s_var, out_ai_start);
        if constexpr (std::is_same<T, char *>::value) {
            if (strcmp(in_data, value) == 0)
                return out_ai_start;
        } else if (in_data == value)
            return out_ai_start;
        for (int i_start_index = 0; i_start_index < in_s_var.i_ndims
        && i_index + 1 < in_s_var.i_data_size; i_start_index++) {
            if ((out_ai_start[i_start_index] + 1 == in_s_var.ai_dims_size[i_start_index] && i_start_index == 0)
            || out_ai_start[i_start_index] == in_s_var.ai_dims_size[i_start_index]) {
                out_ai_start[i_start_index] = 0;
                out_ai_start[i_start_index + 1] += 1;
            } else if (i_start_index == 0) {
                out_ai_start[i_start_index] += 1;
                break;
            }
        }
    }
    return out_ai_start;
}

/**
 * @brief Get the output start index from the start index of an input variable
 * @param in_i_file The file input index
 * @param in_s_input_var The input variable
 * @param in_s_output_var The output variable
 * @param in_ai_input_start The input start index
 * @return <b>size_t *</b> The start index
 */
size_t *assembler::get_start_from_input(size_t in_i_file, variable_information_t & in_s_input_var,
                                        variable_information_t & in_s_output_var, size_t *in_ai_input_start)
{
    size_t *out_ai_start = (size_t *)calloc(in_s_output_var.i_ndims + 1, sizeof(size_t));
    variable_information_t s_dim_var_input = {0};
    variable_information_t s_dim_var_output = {0};

    for (int32_t i_index_dim = 0; i_index_dim < in_s_input_var.i_ndims; i_index_dim++) {
        s_dim_var_input = get_variable_from_dim_id(_vs_input_files[in_i_file], in_s_input_var.ai_dimids[i_index_dim]);
        s_dim_var_output = get_variable_from_dim_id(_s_output_file, in_s_output_var.ai_dimids[i_index_dim]);
        switch (s_dim_var_output.i_type) {
            case 1:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<signed char>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 2:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<char>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 3:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<short>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 4:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<int>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 5:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<float>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 6:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<double>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 7:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<unsigned char>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 8:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<unsigned short>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 9:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<unsigned int>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 10:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<long long>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 11:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<unsigned long long>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 12:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<char *>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            default:
                out_ai_start[i_index_dim] = get_index_from_value(_s_output_file, s_dim_var_output,
                    get_var_value<int>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
        }
    }
    return out_ai_start;
}

/**
 * @brief Add data to a dimension variable from an input dimension variable
 * @param in_i_file The file input index
 * @param in_s_input_var The input variable
 * @param in_s_output_var The output variable
 * @return <b>void</b>
 */
void assembler::add_data_to_dim_variable(size_t in_i_file,
                                         variable_information_t & in_s_input_var,
                                         variable_information_t & in_s_output_var)
{
    int32_t ec = 0;
    static size_t ai_count[NC_MAX_VAR_DIMS] = {0};
    size_t *ai_input_start = (size_t *)calloc(in_s_input_var.i_ndims, sizeof(size_t));
    size_t *ai_output_start = get_end_variable_start(_s_output_file, in_s_output_var);
    auto f_update_output_start = [this, &in_s_output_var, &ai_output_start]() {
        update_variable_size(_s_output_file, in_s_output_var);
        for (int i_start_index = 0; i_start_index < in_s_output_var.i_ndims; i_start_index++) {
            if ((ai_output_start[i_start_index] == in_s_output_var.ai_dims_size[i_start_index] && i_start_index == 0)
            || ai_output_start[i_start_index] - 1 == in_s_output_var.ai_dims_size[i_start_index]) {
                ai_output_start[i_start_index] = 0;
                ai_output_start[i_start_index + 1] += 1;
            } else if (i_start_index == 0) {
                ai_output_start[i_start_index] += 1;
                break;
            }
        }
    };

    for (int32_t i_count_index = 0; i_count_index < NC_MAX_VAR_DIMS; i_count_index++)
        ai_count[i_count_index] = 1;
    update_variable_size(_s_output_file, in_s_output_var);
    for (size_t index = 0; index < in_s_input_var.i_data_size; index++) {
        switch (in_s_output_var.i_type) {
            case 1: {
                signed char value = get_var_value<signed char>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 2: {
                char value = get_var_value<char>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 3: {
                short value = get_var_value<short>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 4: {
                int value = get_var_value<int>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 5: {
                float value = get_var_value<float>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 6: {
                double value = get_var_value<double>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 7: {
                unsigned char value = get_var_value<unsigned char>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 8: {
                unsigned short value = get_var_value<unsigned short>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 9: {
                unsigned int value = get_var_value<unsigned int>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 10: {
                long long value = get_var_value<long long>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 11: {
                unsigned long long value = get_var_value<unsigned long long>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } case 12: {
                char *value = get_var_value<char *>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            } default: {
                int value = get_var_value<int>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                if (data_is_in_variable(_s_output_file, in_s_output_var, value) == false) {
                    set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                    f_update_output_start();
                }
                break;
            }
        }
        for (int i_start_index = 0; i_start_index < in_s_input_var.i_ndims
        && index + 1 < in_s_input_var.i_data_size; i_start_index++) {
            if ((ai_input_start[i_start_index] + 1 == in_s_input_var.ai_dims_size[i_start_index] && i_start_index == 0)
            || ai_input_start[i_start_index] == in_s_input_var.ai_dims_size[i_start_index]) {
                ai_input_start[i_start_index] = 0;
                ai_input_start[i_start_index + 1] += 1;
            } else if (i_start_index == 0) {
                ai_input_start[i_start_index] += 1;
                break;
            }
        }
    }
    free(ai_input_start);
    free(ai_output_start);
}

/**
 * @brief Add data to a variable from an input variable
 * @param in_i_file The file input index
 * @param in_s_input_var The input variable
 * @param in_s_output_var The output variable
 * @return <b>void</b>
 */
void assembler::add_data_to_variable(size_t in_i_file,
                                     variable_information_t & in_s_input_var,
                                     variable_information_t & in_s_output_var)
{
    int32_t ec = 0;
    static size_t ai_count[NC_MAX_VAR_DIMS] = {0};

    update_variable_size(_s_output_file, in_s_output_var);
    size_t *ai_input_start = (size_t *)calloc(in_s_input_var.i_ndims, sizeof(size_t));
    for (int32_t i_count_index = 0; i_count_index < NC_MAX_VAR_DIMS; i_count_index++)
        ai_count[i_count_index] = 1;
    size_t *ai_output_start = get_start_from_input(in_i_file, in_s_input_var, in_s_output_var, ai_input_start);
    size_t *ai_output_start_ref = get_start_from_input(in_i_file, in_s_input_var, in_s_output_var, ai_input_start);
    float *value = NULL;
    for (size_t index = 0; index < in_s_input_var.i_data_size; index++) {
        switch (in_s_output_var.i_type) {
            case 1: {
                signed char value = get_var_value<signed char>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 2: {
                char value = get_var_value<char>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 3: {
                short value = get_var_value<short>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 4: {
                int value = get_var_value<int>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 5: {
                float value = get_var_value<float>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 6: {
                double value = get_var_value<double>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 7: {
                unsigned char value = get_var_value<unsigned char>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 8: {
                unsigned short value = get_var_value<unsigned short>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 9: {
                unsigned int value = get_var_value<unsigned int>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 10: {
                long long value = get_var_value<long long>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 11: {
                unsigned long long value = get_var_value<unsigned long long>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } case 12: {
                char *value = get_var_value<char *>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            } default: {
                int value = get_var_value<int>(_vs_input_files[in_i_file], in_s_input_var, ai_input_start);
                set_var_value(_s_output_file, in_s_output_var, ai_output_start, value);
                break;
            }
        }
        for (int i_start_index = 0; i_start_index < in_s_input_var.i_ndims
        && index + 1 < in_s_input_var.i_data_size; i_start_index++) {
            if ((ai_input_start[i_start_index] + 1 == in_s_input_var.ai_dims_size[i_start_index] && i_start_index == 0)
            || ai_input_start[i_start_index] == in_s_input_var.ai_dims_size[i_start_index]) {
                ai_input_start[i_start_index] = 0;
                ai_input_start[i_start_index + 1] += 1;
                ai_output_start[i_start_index] = ai_output_start_ref[i_start_index];
                ai_output_start[i_start_index + 1] += 1;
            } else if (i_start_index == 0) {
                ai_input_start[i_start_index] += 1;
                ai_output_start[i_start_index] += 1;
                break;
            }
        }
    }
    free(ai_input_start);
    free(ai_output_start);
    free(ai_output_start_ref);
    std::cout << "Fill: FILE = " << _vs_input_files[in_i_file].ac_path
        << " | VAR = " << in_s_output_var.ac_var_name << std::endl;
}

/**
 * @brief Copy the variables
 * @return <b>void</b>
 */
void assembler::copy_variables(void)
{
    int32_t ec = 0;

    for (size_t i_input_index = 0; i_input_index < _vs_input_files.size(); i_input_index++) {
        for (int32_t i_var_index = 0; i_var_index < _vs_input_files[i_input_index].i_nb_variables; i_var_index++) {
            variable_information_t s_new_var = {0};
            variable_information_t s_current_var = {0};
            s_current_var.i_id = i_var_index;

            ec = nc_inq_var(_vs_input_files[i_input_index].i_file_id,
                s_current_var.i_id, s_current_var.ac_var_name,
                &s_current_var.i_type, &s_current_var.i_ndims,
                s_current_var.ai_dimids, &s_current_var.i_natts);
            if (ec != 0) {
                DEBUG;
                fprintf(stderr, RED BOLD "Get variable information:" RESET RED " %s: %s: %s\n" RESET,
                    _vs_input_files[i_input_index].ac_path, s_current_var.ac_var_name, nc_strerror(ec));
                std::exit(EXIT_FAILURE);
            }
            if (s_current_var.i_type < 0 || s_current_var.i_type > 12)
                s_current_var.i_type = 0;
            ec = nc_inq_varid(_s_output_file.i_file_id, s_current_var.ac_var_name, &s_new_var.i_id);
            if (ec != 0) {
                for (int32_t i_index_dim = 0; i_index_dim < s_current_var.i_ndims; i_index_dim++)
                    s_new_var.ai_dimids[i_index_dim] = _vs_input_files[i_input_index].
                        vs_dims[s_current_var.ai_dimids[i_index_dim]].i_output_id;
                ec = nc_def_var(_s_output_file.i_file_id, s_current_var.ac_var_name,
                s_current_var.i_type, s_current_var.i_ndims, s_new_var.ai_dimids, &s_new_var.i_id);
                if (ec != 0) {
                    DEBUG;
                    fprintf(stderr, RED BOLD "Set variable:" RESET RED " %s: %s: %s\n" RESET,
                        _s_output_file.ac_path, s_current_var.ac_var_name, nc_strerror(ec));
                    std::exit(EXIT_FAILURE);
                }
                strcpy(s_new_var.ac_var_name, s_current_var.ac_var_name);
                s_new_var.i_ndims = s_current_var.i_ndims;
                s_new_var.i_type = s_current_var.i_type;
                ERROR(nc_inq_dimid(_s_output_file.i_file_id, s_new_var.ac_var_name, &s_new_var.i_dim_id));
                copy_attributes(i_input_index, s_current_var, s_new_var);
                _s_output_file.vs_variables.push_back(s_new_var);
                std::cout << "Add: FILE = " << _vs_input_files[i_input_index].ac_path
                    << " | VAR = " << s_current_var.ac_var_name << std::endl;
            }
            s_current_var.i_output_id = s_new_var.i_id;
            update_variable_size(_vs_input_files[i_input_index], s_current_var);
            ERROR(nc_inq_dimid(_vs_input_files[i_input_index].i_file_id, s_current_var.ac_var_name, &s_current_var.i_dim_id));
            if (_s_output_file.vs_variables[s_new_var.i_id].i_dim_id != -1) {
                add_data_to_dim_variable(i_input_index, s_current_var, _s_output_file.vs_variables[s_new_var.i_id]);
                std::cout << "Fill: FILE = " << _vs_input_files[i_input_index].ac_path
                    << " | VAR = " << s_current_var.ac_var_name << std::endl;
            }
            _vs_input_files[i_input_index].vs_variables.push_back(s_current_var);
        }
    }
    get_info(_s_output_file);
    for (int32_t i_var_index = 0; i_var_index < _s_output_file.i_nb_variables; i_var_index++) {
        if (_s_output_file.vs_variables[i_var_index].i_dim_id != -1)
            sort_variable(_s_output_file.vs_variables[i_var_index]);
    }
    for (size_t i_input_index = 0; i_input_index < _vs_input_files.size(); i_input_index++) {
        for (int32_t i_var_index = 0; i_var_index < _vs_input_files[i_input_index].i_nb_variables; i_var_index++) {
            if (_vs_input_files[i_input_index].vs_variables[i_var_index].i_dim_id == -1)
                add_data_to_variable(i_input_index, _vs_input_files[i_input_index].vs_variables[i_var_index],
                    _s_output_file.vs_variables[_vs_input_files[i_input_index].vs_variables[i_var_index].i_output_id]);
        }
    }
}