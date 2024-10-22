/*
** SEAGNAL PROJECT, 2024
** netcdf-assembler
** File description:
** The file containing the dimensions functions
*/
/**
 * @file dimensions.cc
 * @brief The file containing the dimensions functions
 * @author Nicolas TORO
 */

#include "../include/nc_assembler.hh"

size_t f_get_dimension_size(file_informations_t & in_s_file_infos, size_t in_i_dim_id)
{
    size_t i_dim_len = 0;
    int32_t ec = nc_inq_dimlen(in_s_file_infos.i_file_id, in_i_dim_id, &i_dim_len);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get dimension lenght:" RESET RED " %s: id = %zu: %s\n" RESET,
            in_s_file_infos.ac_path, in_i_dim_id, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    return i_dim_len;
}

variable_informations_t assembler::f_get_variable_from_dim_id(file_informations_t & in_s_file, size_t in_i_dim_id)
{
    for (int32_t i_index_var = 0; i_index_var < in_s_file.i_nb_variables; i_index_var++) {
        if (in_s_file.vs_variables[i_index_var].i_dim_id == in_i_dim_id)
            return in_s_file.vs_variables[i_index_var];
    }
    DEBUG;
    fprintf(stderr, RED BOLD "Get variable from dim:" RESET RED " %s: Cannot find variable of dim %zu\n" RESET,
        in_s_file.ac_path, in_i_dim_id);
    std::exit(EXIT_FAILURE);
}

void assembler::f_copy_dimensions(void)
{
    int32_t ec = 0;

    for (size_t i_input_index = 0; i_input_index < _vs_input_files.size(); i_input_index++) {
        for (int32_t i_dim_index = 0; i_dim_index < _vs_input_files[i_input_index].i_nb_dimensions; i_dim_index++) {
            dimension_informations_s s_current_dim;

            ec = nc_inq_dim(_vs_input_files[i_input_index].i_file_id, i_dim_index, s_current_dim.ac_dim_name, &s_current_dim.i_dim_len);
            if (ec != 0) {
                DEBUG;
                fprintf(stderr, RED BOLD "Get dimension informations:" RESET RED " %s: %s: %s\n" RESET,
                    _vs_input_files[i_input_index].ac_path, s_current_dim.ac_dim_name, nc_strerror(ec));
                std::exit(EXIT_FAILURE);
            }
            ec = nc_inq_dimid(_s_output_file.i_file_id, s_current_dim.ac_dim_name, &s_current_dim.i_output_id);
            if (ec != 0) {
                ec = nc_def_dim(_s_output_file.i_file_id, s_current_dim.ac_dim_name, NC_UNLIMITED, &s_current_dim.i_output_id);
                if (ec != 0) {
                    DEBUG;
                    fprintf(stderr, RED BOLD "Set dimension:" RESET RED " %s: %s: %s\n" RESET,
                        _s_output_file.ac_path, s_current_dim.ac_dim_name, nc_strerror(ec));
                    std::exit(EXIT_FAILURE);
                }
                _s_output_file.vs_dims.push_back(s_current_dim);
            }
            _vs_input_files[i_input_index].vs_dims.push_back(s_current_dim);
        }
    }
}