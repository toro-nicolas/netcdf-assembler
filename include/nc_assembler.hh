/*
** SEAGNAL PROJECT, 2024
** netcdf-assembler
** File description:
** The header file of the project
*/
/**
 * @file nc_assembler.hh
 * @brief The header file of the project
 * @author Nicolas TORO
 */

#include <algorithm>
#include <cerrno>
#include <cmath>
#include <cstdbool>
#include <cstddef>
#include <cstdint>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <fcntl.h>
#include <iostream>
#include <libgen.h>
#include <linux/limits.h>
#include <netcdf.h>
#include <stdexcept>
#include <unistd.h>
#include <variant>
#include <vector>
#include <wait.h>

#ifndef NC_ASSEMBLER_HH_
    #define NC_ASSEMBLER_HH_

    #define RED "\033[0;31m"
    #define YELLOW "\033[0;33m"
    #define BOLD "\033[1m"
    #define UNDERLINE "\033[4m"
    #define RESET "\033[0m"
    #ifdef DEBUG_MODE
        #define DEBUG (std::cout << YELLOW << "FILE: " << __FILE__ << ":" << __LINE__ << ", FUNCTION: " << __PRETTY_FUNCTION__ << RESET << std::endl)
    #else
        #define DEBUG
    #endif
    #define ERROR(ec) check_error(ec, __FILE__, __LINE__, __PRETTY_FUNCTION__)

/* The variable types */
using var_type = std::variant<signed char, char, short, int, float, double, unsigned char, unsigned short, unsigned int, long long, unsigned long long, char *>;

/* The dimension information */
typedef struct dimension_information_s {
    int32_t i_output_id = -1; /* The output id */
    char ac_dim_name[NC_MAX_NAME + 1] = {0}; /* The dimension name */
    size_t i_dim_len = 0; /* The dimension length */
} dimension_information_t;

/* The variable information */
typedef struct variable_information_s {
    int32_t i_id = 0; /* The variable id */
    char ac_var_name[NC_MAX_NAME + 1] = {0}; /* The variable name */
    nc_type i_type = 0; /* The variable type */
    int32_t i_ndims = 0; /* The number of dimensions */
    int32_t ai_dimids[NC_MAX_VAR_DIMS] = {0}; /* The dimensions ids */
    int32_t i_natts = 0; /* The number of attributes */
    size_t ai_dims_size[NC_MAX_VAR_DIMS] = {0}; /* The dimensions size */
    size_t i_data_size = 0; /* The data size */
    int32_t i_dim_id = -1; /* The dimension id (for dimension variable) */
    int32_t i_output_id = -1; /* The output id */
} variable_information_t;

/* The file information */
typedef struct file_information_s {
    char *ac_path = {0}; /* The file path */
    int32_t i_file_id = 0; /* The file id */
    int32_t i_nb_dimensions = 0; /* The number of dimensions */
    int32_t i_nb_variables = 0; /* The number of variables */
    int32_t i_nb_attributes = 0; /* The number of attributes */
    int32_t i_first_unlimited_dimensions_id = 0; /* The first unlimited dimension id */
    std::vector<dimension_information_t> vs_dims; /* The dimensions */
    std::vector<variable_information_t> vs_variables; /* The variables */
} file_information_t;

class assembler {
    protected:
        std::vector<file_information_t> _vs_input_files;
        file_information_t _s_output_file = {0};

    public:
        /**
         * @brief The assembler class constructor
         */
        assembler(int argc, char **argv);

        /**
        * @brief The assembler class destructor
        */
        ~assembler();



            /* Attributes functions */

        /**
        * @brief Copy the attributes from the input file to the output file
        * @param in_i_input_file The index of the input file
        * @param in_s_ref_var The variable information of the input file
        * @param in_s_fill_var The variable information of the output file
        * @return <b>void</b>
        */
        void copy_attributes(int32_t in_i_input_file, variable_information_t & in_s_ref_var,
                             variable_information_t & in_s_fill_var);

        /**
        * @brief Add the global attributes to the output file
        * and copy globals attributes from first input file
        * @return <b>void</b>
        */
        void add_globals_attributes(void);



            /* Dimensions functions */

        /**
         * @brief Get the variable from the dimension id
         * @param in_s_file The file information
         * @param in_i_dim_id The dimension id
         * @return <b>variable_information_t</b> The variable information
         */
        variable_information_t get_variable_from_dim_id(file_information_t & in_s_file,
                                                        size_t in_i_dim_id);

        /**
        * @brief Copy the dimensions from the input files to the output file
        * @return <b>void</b>
        */
        void copy_dimensions(void);



            /* Variables functions */

        /**
        * @brief Sort a variable
        * @param in_s_current_var The variable to sort
        * @return <b>void</b>
        */
        void sort_variable(variable_information_t & in_s_current_var);

        /**
        * @brief Get the output start index from the start index of an input variable
        * @param in_i_file The file input index
        * @param in_s_input_var The input variable
        * @param in_s_output_var The output variable
        * @param in_ai_input_start The input start index
        * @return <b>size_t *</b> The start index
        */
        size_t *get_start_from_input(size_t in_i_file, variable_information_t & in_s_input_var,
                                     variable_information_t & in_s_output_var, size_t *in_ai_input_start);

        /**
        * @brief Add data to a dimension variable from an input dimension variable
        * @param in_i_file The file input index
        * @param in_s_input_var The input variable
        * @param in_s_output_var The output variable
        * @return <b>void</b>
        */
        void add_data_to_dim_variable(size_t in_i_file,
                                      variable_information_t & in_s_input_var,
                                      variable_information_t & in_s_output_var);

        /**
        * @brief Add data to a variable from an input variable
        * @param in_i_file The file input index
        * @param in_s_input_var The input variable
        * @param in_s_output_var The output variable
        * @return <b>void</b>
        */
        void add_data_to_variable(size_t in_i_file,
                                  variable_information_t & in_s_input_var,
                                  variable_information_t & in_s_output_var);

        /**
        * @brief Copy the variables
        * @return <b>void</b>
        */
        void copy_variables(void);
};



    /* Generale functions */

/**
 * @brief Check if there is an error
 * @param in_i_error The error code
 * @param in_ac_file The file name
 * @param in_i_line The line number
 * @param in_ac_func The function name
 * @return <b>void</b>
 */
void check_error(int in_i_error, const char *in_ac_file,
                 const int in_i_line, const char *in_ac_func);

/**
 * @brief Open a NetCDF or a GRIB file
 * @param in_s_file_info The file information
 * @param in_i_mode The mode to open the file
 * @return <b>void</b>
 */
void open_file(file_information_t & in_s_file_info, int in_i_mode);

/**
 * @brief Create a NetCDF file
 * @param in_s_file_info The file information
 * @param in_i_mode The mode to open the file
 * @return <b>void</b>
 */
void create_file(file_information_t & in_s_file_info, int in_i_mode);

/**
 * @brief Get the file information
 * @param in_s_file_info The file information
 * @return <b>void</b>
 */
void get_info(file_information_t & in_s_file_info);

/**
 * @brief Close a NetCDF file
 * @param in_s_file_info The file information
 * @return <b>void</b>
 */
void close_file(file_information_t & in_s_file_info);

/**
 * @brief Get the dimension size
 * @param in_s_file_info The file information
 * @param in_i_dim_id The dimension id
 * @return <b>size_t</b> The dimension size
 */
size_t get_dimension_size(file_information_t & in_s_file_info, size_t in_i_dim_id);



#endif /* NC_ASSEMBLER_HH_ */
