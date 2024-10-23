/*
** SEAGNAL PROJECT, 2024
** netcdf-assembler
** File description:
** The file containing the sort functions
*/
/**
 * @file sort.cc
 * @brief The file containing the sort functions
 * @author Nicolas TORO
 */

#include "../include/nc_assembler.hh"

/**
 * @brief Sort an invalid variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_invalid(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    DEBUG;
    fprintf(stderr, RED BOLD "Cannot sort:" RESET RED " %s: %s\n" RESET, 
    in_s_file.ac_path, in_s_var.ac_var_name);
}

/**
 * @brief Sort a byte variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_byte(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort a char variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_char(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort a short variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_short(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort an int variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_int(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort a float variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_float(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort a double variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_double(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort an unsigned byte variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_ubyte(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort an unsigned short variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_ushort(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort an unsigned int variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_uint(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort an int64 variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_int64(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort an unsigned int64 variable
 * @param in_s_file The file information
 * @param in_s_var The variable to sort
 * @return <b>void</b>
 */
void sort_uint64(file_information_t & in_s_file, variable_information_t & in_s_var)
{
    std::vector<double> data(in_s_var.i_data_size);
    int32_t ec = nc_get_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    std::sort(data.begin(), data.end());
    ec = nc_put_var_double(in_s_file.i_file_id, in_s_var.i_id, data.data());
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Sort variable:" RESET RED " %s: %s: %s\n" RESET, 
        in_s_file.ac_path, in_s_var.ac_var_name, strerror(ec));
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Sort a variable
 * @param in_s_current_var The variable to sort
 * @return <b>void</b>
 */
void assembler::sort_variable(variable_information_t & in_s_current_var)
{
    static void (*sort_functions[])(file_information_t & in_s_file,
    variable_information_t & in_s_var) = {
      &sort_invalid, &sort_byte, &sort_invalid, &sort_short, &sort_int,
      &sort_float, &sort_double, &sort_ubyte, &sort_ushort, &sort_uint,
      &sort_int64, &sort_uint64, &sort_invalid};

    sort_functions[in_s_current_var.i_type](_s_output_file, in_s_current_var);
    if (in_s_current_var.i_type > 0 && in_s_current_var.i_type < 12)
        std::cout << "Sort: FILE = " << _s_output_file.ac_path
            << " | VAR = " << in_s_current_var.ac_var_name << std::endl;
}
