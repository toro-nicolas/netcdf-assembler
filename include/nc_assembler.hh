/*
** SEAGNAL PROJECT, 2024
** netcdf-zone-selector
** File description:
** The header file of the project
*/
/**
 * @file nc_zone_selector.h
 * @brief The header file of the project
 * @author Nicolas TORO
 */

#include <netcdf.h>
//#include <hdf5.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <math.h>
#include <iostream>
#include <vector>
#include <stdexcept>
#include <variant>

#ifndef NC_ASSEMBLER_HH_
    #define NC_ASSEMBLER_HH_

    #define RED "\033[0;31m"
    #define YELLOW "\033[0;33m"
    #define BOLD "\033[1m"
    #define UNDERLINE "\033[4m"
    #define RESET "\033[0m"
    #define DEBUG (std::cout << YELLOW << "FILE: " << __FILE__ << ":" << __LINE__ << ", FUNCTION: " << __PRETTY_FUNCTION__ << RESET << std::endl)

typedef struct dimension_informations_s {
    int32_t i_output_id = -1;
    char ac_dim_name[NC_MAX_NAME + 1] = {0};
    size_t i_dim_len = 0;
} dimension_informations_t;

typedef struct variable_informations_s {
    int32_t i_id = 0;
    char ac_var_name[NC_MAX_NAME + 1] = {0};
    nc_type i_type = 0;
    int32_t i_ndims = 0;
    int32_t ai_dimids[NC_MAX_VAR_DIMS] = {0};
    int32_t i_natts = 0;
    size_t ai_dims_size[NC_MAX_VAR_DIMS] = {0};
    size_t i_data_size = 0;
    int32_t i_dim_id = -1;
    int32_t i_output_id = -1;
} variable_informations_t;

typedef struct file_informations_s {
    char *ac_path = {0};
    int32_t i_file_id = 0;
    int32_t i_nb_dimensions = 0;
    int32_t i_nb_variables = 0;
    int32_t i_nb_attributes = 0;
    int32_t i_first_unlimited_dimensions_id = 0;
    int32_t i_latitude_dim_id = -1;
    int32_t i_longitude_dim_id = -1;
    int32_t i_depth_dim_id = -1;
    std::vector<dimension_informations_t> vs_dims;
    std::vector<variable_informations_t> vs_variables;
} file_informations_t;

class assembler {
    protected:
        double _d_resolution = 0;
        std::vector<file_informations_t> _vs_input_files;
        file_informations_t _s_output_file = {0};

    public:
        assembler(int argc, char **argv);
        ~assembler();

        /* Attributes functions */
        void f_add_globals_attributes(void);

        /* Dimensions functions */
        variable_informations_t f_get_variable_from_dim_id(file_informations_t & in_s_file,
                                                           size_t in_i_dim_id);
        int32_t *f_convert_dims_list(size_t i_file, int32_t i_nb_dims, int32_t *ai_dim_list);
        void f_copy_dimensions(void);

        /* Variables functions */
        size_t *f_get_start_from_input(size_t in_i_file, variable_informations_t & in_s_input_var,
                                       variable_informations_t & in_s_output_var, size_t *in_ai_input_start);
        void f_add_data_to_dim_variable(size_t in_i_file, 
                                        variable_informations_t & in_s_input_var,
                                        variable_informations_t & in_s_output_var);
        void f_add_data_to_variable(size_t in_i_file, 
                                    variable_informations_t & in_s_input_var,
                                    variable_informations_t & in_s_output_var);
        void f_copy_variables(void);
};

/* Generale functions */
void f_open_file(file_informations_t & in_s_file_infos, int in_i_mode);
void f_create_file(file_informations_t & in_s_file_infos, int in_i_mode);
void f_get_infos(file_informations_t & in_s_file_infos);
void f_close_file(file_informations_t & in_s_file_infos);
size_t f_get_dimension_size(file_informations_t & in_s_file_infos, size_t in_i_dim_id);

#endif /* NC_ASSEMBLER_HH_ */
