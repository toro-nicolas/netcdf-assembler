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

#include "../include/nc_assembler.hh"

void f_update_variable_size(file_informations_t & in_s_file, variable_informations_t & in_s_var)
{
    in_s_var.i_data_size = 1;
    for (int32_t i_dim_index = 0; i_dim_index < in_s_var.i_ndims; i_dim_index++) {
        in_s_var.ai_dims_size[i_dim_index] = f_get_dimension_size(in_s_file, in_s_var.ai_dimids[i_dim_index]);
        in_s_var.i_data_size *= in_s_var.ai_dims_size[i_dim_index]; 
    }
}

size_t *f_get_end_variable_start(file_informations_t & in_s_file, variable_informations_t & in_s_var)
{
    size_t *out_ai_start = (size_t *)calloc(in_s_var.i_ndims, sizeof(size_t));

    for (int32_t i_dim_index = 0; i_dim_index < in_s_var.i_ndims; i_dim_index++)
        out_ai_start[i_dim_index] = in_s_var.ai_dims_size[i_dim_index];
    return out_ai_start;
}

using var_type = std::variant<signed char, char, short, int, float, double, unsigned char, unsigned short, unsigned int, long long, unsigned long long, char *>;

var_type get_invalid_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                           size_t *in_ai_count, size_t *in_ai_start)
{
    DEBUG;
    fprintf(stderr, RED BOLD "Get an invalid value:" RESET RED " %s: %s\n" RESET, 
    in_s_file.ac_path, in_s_var.ac_var_name);
    free(in_ai_start);
    std::exit(EXIT_FAILURE);
}

var_type get_byte_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                        size_t *in_ai_count, size_t *in_ai_start)
{
    signed char out_value[1] = {0};
    int32_t ec = nc_get_vara_schar(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_char_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                        size_t *in_ai_count, size_t *in_ai_start)
{
    char out_value[1] = {0};
    int32_t ec = nc_get_vara_text(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_short_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                         size_t *in_ai_count, size_t *in_ai_start)
{
    short out_value[1] = {0};
    int32_t ec = nc_get_vara_short(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_int_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                       size_t *in_ai_count, size_t *in_ai_start)
{
    int out_value[1] = {0};
    int32_t ec = nc_get_vara_int(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_float_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                         size_t *in_ai_count, size_t *in_ai_start)
{
    float out_value[1] = {0};
    int32_t ec = nc_get_vara_float(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_double_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                          size_t *in_ai_count, size_t *in_ai_start)
{
    double out_value[1] = {0};
    int32_t ec = nc_get_vara_double(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);

    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_ubyte_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                         size_t *in_ai_count, size_t *in_ai_start)
{
    unsigned char out_value[1] = {0};
    int32_t ec = nc_get_vara_ubyte(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_ushort_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                          size_t *in_ai_count, size_t *in_ai_start)
{
    unsigned short out_value[1] = {0};
    int32_t ec = nc_get_vara_ushort(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_uint_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                        size_t *in_ai_count, size_t *in_ai_start)
{
    unsigned int out_value[1] = {0};
    int32_t ec = nc_get_vara_uint(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_int64_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                         size_t *in_ai_count, size_t *in_ai_start)
{
    long long out_value[1] = {0};
    int32_t ec = nc_get_vara_longlong(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_uint64_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                          size_t *in_ai_count, size_t *in_ai_start)
{
    unsigned long long out_value[1] = {0};
    int32_t ec = nc_get_vara_ulonglong(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

var_type get_string_value(file_informations_t & in_s_file, variable_informations_s & in_s_var,
                          size_t *in_ai_count, size_t *in_ai_start)
{
    char *out_value[1] = {0};
    int32_t ec = nc_get_vara_string(in_s_file.i_file_id, in_s_var.i_id, in_ai_start, in_ai_count, out_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get variable value:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        free(in_ai_start);
        std::exit(EXIT_FAILURE);
    }
    return out_value[0];
}

template <typename T>
T f_get_var_value(file_informations_t & in_s_file, variable_informations_s & in_s_current_var,
                  size_t *in_ai_start)
{
    static var_type (*get_value_functions[])(file_informations_t & in_s_file,
    variable_informations_s & in_s_var, size_t *in_ai_count, size_t *in_ai_start) = {
      &get_invalid_value, &get_byte_value, &get_char_value,
      &get_short_value, &get_int_value,
      &get_float_value, &get_double_value, &get_ubyte_value,
      &get_ushort_value, &get_uint_value, &get_int64_value,
      &get_uint64_value, &get_string_value};
    static size_t ai_count[NC_MAX_VAR_DIMS] = {0};

    if (ai_count[0] == 0) { 
        for (int32_t i_count_index = 0; i_count_index < NC_MAX_VAR_DIMS; i_count_index++)
            ai_count[i_count_index] = 1;
    }
    return std::get<T>(get_value_functions[in_s_current_var.i_type](in_s_file, in_s_current_var, ai_count, in_ai_start));
}

template <typename T>
bool f_data_is_in_variable(file_informations_t & in_s_file, variable_informations_t & in_s_var, T in_data)
{
    size_t *ai_start = (size_t *)calloc(in_s_var.i_ndims + 1, sizeof(size_t));

    for (size_t i_index = 0; i_index < in_s_var.i_data_size; i_index++) {
        T value = f_get_var_value<T>(in_s_file, in_s_var, ai_start);
        if constexpr (std::is_same<T, char *>::value) {
            if (strcmp(in_data, value) == 0) {
                free(ai_start);
                return true;
            }
        } else if (in_data == value) {
            free(ai_start);
            return true;
        }

        for (int i_start_index = in_s_var.i_ndims - 1;
        i_start_index > -1 && i_index + 1 < in_s_var.i_data_size; i_start_index--) {
            if (ai_start[i_start_index] + 1 == in_s_var.ai_dims_size[i_start_index]) {
                ai_start[i_start_index] = 0;
                ai_start[i_start_index - 1] += 1;
            } else if (i_start_index == in_s_var.i_ndims - 1) {
                ai_start[i_start_index] += 1;
                break;
            }
        }
    }
    free(ai_start);
    return false;
}

void assembler::f_add_data_to_dim_variable(size_t in_i_file, 
                                           variable_informations_t & in_s_input_var,
                                           variable_informations_t & in_s_output_var)
{
    int32_t ec = 0;
    static size_t ai_count[NC_MAX_VAR_DIMS] = {0};
    size_t *ai_input_start = (size_t *)calloc(in_s_input_var.i_ndims, sizeof(size_t));
    size_t *ai_output_start = f_get_end_variable_start(_s_output_file, in_s_output_var);
    double *value = NULL;

    for (int32_t i_count_index = 0; i_count_index < NC_MAX_VAR_DIMS; i_count_index++)
        ai_count[i_count_index] = 1;
    f_update_variable_size(_s_output_file, in_s_output_var);
    for (size_t index = 0; index < in_s_input_var.i_data_size; index++) {
        /*for (size_t i_index_dim = 0; i_index_dim < in_s_input_var.i_ndims; i_index_dim++)
            std::cout << "in: " << ai_input_start[i_index_dim] << " ";
        std::cout << std::endl;
        for (size_t i_index_dim = 0; i_index_dim < in_s_output_var.i_ndims; i_index_dim++)
            std::cout << "out: " << ai_output_start[i_index_dim] << " ";
        std::cout << std::endl;*/
        value = (double *)calloc(1, sizeof(double *));
        nc_get_vara_double(_vs_input_files[in_i_file].i_file_id, in_s_input_var.i_id, ai_input_start, ai_count, value);
        if (f_data_is_in_variable(_s_output_file, in_s_output_var, *value) == false) {
            nc_put_var1_double(_s_output_file.i_file_id, in_s_output_var.i_id, ai_output_start, value);
            f_update_variable_size(_s_output_file, in_s_output_var);
            for (int i_start_index = in_s_output_var.i_ndims - 1; i_start_index > -1; i_start_index--) {
                if (ai_output_start[i_start_index] == in_s_output_var.ai_dims_size[i_start_index]) {
                    ai_output_start[i_start_index] = 0;
                    ai_output_start[i_start_index - 1] += 1;
                } else if (i_start_index == in_s_input_var.i_ndims - 1) {
                    ai_output_start[i_start_index] += 1;
                    break;
                }
            }
        }
        free(value);
        for (int i_start_index = in_s_input_var.i_ndims - 1;
        i_start_index > -1 && index + 1 < in_s_input_var.i_data_size; i_start_index--) {
            if (ai_input_start[i_start_index] + 1 == in_s_input_var.ai_dims_size[i_start_index]) {
                ai_input_start[i_start_index] = 0;
                ai_input_start[i_start_index - 1] += 1;
            } else if (i_start_index == in_s_input_var.i_ndims - 1) {
                ai_input_start[i_start_index] += 1;
                break;
            }
        }
    }
    free(ai_input_start);
    free(ai_output_start);
}

template <typename T>
size_t *f_get_index_from_value(file_informations_t & in_s_file, variable_informations_t & in_s_var, T in_data)
{
    size_t *out_ai_start = (size_t *)calloc(in_s_var.i_ndims, sizeof(size_t));
    for (size_t i_index = 0; i_index < in_s_var.i_data_size; i_index++) {
        T value = f_get_var_value<T>(in_s_file, in_s_var, out_ai_start);
        if constexpr (std::is_same<T, char *>::value) {
            if (strcmp(in_data, value) == 0)
                return out_ai_start;
        } else if (in_data == value)
            return out_ai_start;
        /*for (int i_start_index = in_s_var.i_ndims - 1;
        i_start_index > -1 && i_index + 1 < in_s_var.i_data_size; i_start_index--) {
            if (out_ai_start[i_start_index] + 1 == in_s_var.ai_dims_size[i_start_index]) {
                out_ai_start[i_start_index] = 0;
                out_ai_start[i_start_index - 1] += 1;
            } else if (i_start_index == in_s_var.i_ndims - 1) {
                out_ai_start[i_start_index] += 1;
                break;
            }
        }*/
        for (int i_start_index = 0;
        i_start_index < in_s_var.i_ndims && i_index + 1 < in_s_var.i_data_size; i_start_index++) {
            if (out_ai_start[i_start_index] + 1 == in_s_var.ai_dims_size[i_start_index]) {
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

size_t *assembler::f_get_start_from_input(size_t in_i_file, variable_informations_t & in_s_input_var,
                                          variable_informations_t & in_s_output_var, size_t *in_ai_input_start)
{
    size_t *out_ai_start = (size_t *)calloc(in_s_output_var.i_ndims + 1, sizeof(size_t));
    variable_informations_t s_dim_var_input = {0};
    variable_informations_t s_dim_var_output = {0};

    for (int32_t i_index_dim = 0; i_index_dim < in_s_input_var.i_ndims; i_index_dim++) {
        s_dim_var_input = f_get_variable_from_dim_id(_vs_input_files[in_i_file], in_s_input_var.ai_dimids[i_index_dim]);
        s_dim_var_output = f_get_variable_from_dim_id(_s_output_file, in_s_output_var.ai_dimids[i_index_dim]);
        switch (s_dim_var_output.i_type) {
            case 1:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<signed char>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 2:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<char>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 3:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<short>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 4:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<int>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 5:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<float>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 6:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<double>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 7:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<unsigned char>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 8:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<unsigned short>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 9:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<unsigned int>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 10:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<long long>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 11:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<unsigned long long>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            case 12:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<char *>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
            default:
                out_ai_start[i_index_dim] = f_get_index_from_value(_s_output_file, s_dim_var_output,
                    f_get_var_value<int>(_vs_input_files[in_i_file], s_dim_var_input, &in_ai_input_start[i_index_dim]))[0];
                break;
        }
    }
    return out_ai_start;
}


void assembler::f_add_data_to_variable(size_t in_i_file, 
                                       variable_informations_t & in_s_input_var,
                                       variable_informations_t & in_s_output_var)
{
    int32_t ec = 0;
    static size_t ai_count[NC_MAX_VAR_DIMS] = {0};

    size_t *ai_input_start = (size_t *)calloc(in_s_input_var.i_ndims, sizeof(size_t));
    for (int32_t i_count_index = 0; i_count_index < NC_MAX_VAR_DIMS; i_count_index++)
        ai_count[i_count_index] = 1;
    f_update_variable_size(_s_output_file, in_s_output_var);
    float *value = NULL;
    for (size_t index = 0; index < in_s_input_var.i_data_size; index++) {
        std::cout << "in: " << std::endl;
        for (size_t i_index_dim = 0; i_index_dim < in_s_input_var.i_ndims; i_index_dim++)
            std::cout << ai_input_start[i_index_dim] << " ";
        std::cout << std::endl;
        size_t *ai_output_start = f_get_start_from_input(in_i_file, in_s_input_var, in_s_output_var, ai_input_start);
        std::cout << "out: " << std::endl;
        for (size_t i_index_dim = 0; i_index_dim < in_s_output_var.i_ndims; i_index_dim++)
            std::cout << ai_output_start[i_index_dim] << " ";
        std::cout << std::endl;
        value = (float *)calloc(1, sizeof(float *));
        nc_get_vara_float(_vs_input_files[in_i_file].i_file_id, in_s_input_var.i_id, ai_input_start, ai_count, value);
        //std::cout << "value: " << *value << std::endl;
        nc_put_var1_float(_s_output_file.i_file_id, in_s_output_var.i_id, ai_output_start, value);
        f_update_variable_size(_s_output_file, in_s_output_var);
        free(value);
        free(ai_output_start);
        if (index + 1 < in_s_input_var.i_data_size) {
            for (int i_start_index = 0;
            i_start_index < in_s_input_var.i_ndims && index + 1 < in_s_input_var.i_data_size; i_start_index++) {
                if (ai_input_start[i_start_index] + 1 == in_s_input_var.ai_dims_size[i_start_index]) {
                    ai_input_start[i_start_index] = 0;
                    ai_input_start[i_start_index + 1] += 1;
                    /*DEBUG;
                    if (ai_input_start[i_start_index - 1] >= 1)
                        std::exit(1);*/
                } else if (i_start_index == 0) {
                    ai_input_start[i_start_index] += 1;
                    break;
                }
            }
        }
        std::cout << "index: " << index + 1 << "/" << in_s_input_var.i_data_size << std::endl;
    }
    free(ai_input_start);
}

void assembler::f_copy_variables(void)
{
    int32_t ec = 0;
    int32_t i_tmp_dim_id = 0;

    for (size_t i_input_index = 0; i_input_index < _vs_input_files.size(); i_input_index++) {
        for (int32_t i_var_index = 0; i_var_index < _vs_input_files[i_input_index].i_nb_variables; i_var_index++) {
            variable_informations_s s_new_var = {0};
            variable_informations_t s_current_var = {0};
            s_current_var.i_id = i_var_index;

            ec = nc_inq_var(_vs_input_files[i_input_index].i_file_id, 
                s_current_var.i_id, s_current_var.ac_var_name,
                &s_current_var.i_type, &s_current_var.i_ndims,
                s_current_var.ai_dimids, &s_current_var.i_natts);
            if (ec != 0) {
                DEBUG;
                fprintf(stderr, RED BOLD "Get variable informations:" RESET RED " %s: %s: %s\n" RESET,
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
                nc_inq_dimid(_s_output_file.i_file_id, s_new_var.ac_var_name, &s_new_var.i_dim_id);
                _s_output_file.vs_variables.push_back(s_new_var);
            }
            s_current_var.i_output_id = s_new_var.i_id;
            f_update_variable_size(_vs_input_files[i_input_index], s_current_var);
            nc_inq_dimid(_vs_input_files[i_input_index].i_file_id, s_current_var.ac_var_name, &s_current_var.i_dim_id);
            if (s_new_var.i_dim_id != -1)
                f_add_data_to_dim_variable(i_input_index, s_current_var, _s_output_file.vs_variables[s_new_var.i_id]);
            _vs_input_files[i_input_index].vs_variables.push_back(s_current_var);            
            std::cout << "Update: FILE = " << _vs_input_files[i_input_index].ac_path
                << " | VAR = " << s_current_var.ac_var_name << std::endl;
        }
    }
    f_get_infos(_s_output_file);
    for (size_t i_input_index = 0; i_input_index < _vs_input_files.size(); i_input_index++) {
        for (int32_t i_var_index = 0; i_var_index < _vs_input_files[i_input_index].i_nb_variables; i_var_index++) {
            if (_vs_input_files[i_input_index].vs_variables[i_var_index].i_dim_id == -1)
                f_add_data_to_variable(i_input_index, _vs_input_files[i_input_index].vs_variables[i_var_index],
                    _s_output_file.vs_variables[_vs_input_files[i_input_index].vs_variables[i_var_index].i_output_id]);
        }
    }
}