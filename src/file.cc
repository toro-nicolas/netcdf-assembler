/*
** SEAGNAL PROJECT, 2024
** netcdf-assembler
** File description:
** The file containing the NetCDF file functions
*/
/**
 * @file file.cc
 * @brief The file containing the NetCDF file functions
 * @author Nicolas TORO
 */

#include "../include/nc_assembler.hh"

void f_open_file(file_informations_t & in_s_file_infos, int in_i_mode)
{
    int32_t ec = nc_open(in_s_file_infos.ac_path, in_i_mode, &in_s_file_infos.i_file_id);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Open file:" RESET RED " %s: %s\n" RESET, in_s_file_infos.ac_path, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

void f_create_file(file_informations_t & in_s_file_infos, int in_i_mode)
{
    int32_t ec = nc_create(in_s_file_infos.ac_path, in_i_mode, &in_s_file_infos.i_file_id);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Create file:" RESET RED " %s: %s\n" RESET, in_s_file_infos.ac_path, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

void f_get_infos(file_informations_t & in_s_file_infos)
{
    int32_t ec = nc_inq(in_s_file_infos.i_file_id, &in_s_file_infos.i_nb_dimensions,
        &in_s_file_infos.i_nb_variables, &in_s_file_infos.i_nb_attributes,
        &in_s_file_infos.i_first_unlimited_dimensions_id);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get file informations:" RESET RED " %s: %s\n" RESET, in_s_file_infos.ac_path, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

void f_close_file(file_informations_t & in_s_file_infos)
{
    int32_t ec = nc_close(in_s_file_infos.i_file_id);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Close file:" RESET RED " %s: %s\n" RESET, in_s_file_infos.ac_path, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}


