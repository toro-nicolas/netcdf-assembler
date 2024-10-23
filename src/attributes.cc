/*
** SEAGNAL PROJECT, 2024
** netcdf-assembler
** File description:
** The file containing the attributes functions
*/
/**
 * @file attributes.cc
 * @brief The file containing the attributes functions
 * @author Nicolas TORO
 */

#include "../include/nc_assembler.hh"

/**
 * @brief Copy a invalid attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_invalid(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                            variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                            int32_t i_att_len, char *in_ac_att_name)
{
    DEBUG;
    fprintf(stderr, RED BOLD "Unable to copy attribute:" RESET RED " %s: %s: %s: invalid attribute type\n" RESET, 
    in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name);
    std::exit(EXIT_FAILURE);
}

/**
 * @brief Copy a byte attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_byte(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                         variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                         int32_t i_att_len, char *in_ac_att_name)
{
    signed char *value = (signed char *)calloc(i_att_len, sizeof(signed char));
    int32_t ec = nc_get_att_schar(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_schar(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, NC_BYTE, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy a char attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_char(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                         variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                         int32_t i_att_len, char *in_ac_att_name)
{
    char *value = (char *)calloc(i_att_len, sizeof(char));
    int32_t ec = nc_get_att_text(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_text(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy a short attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_short(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                          variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                          int32_t i_att_len, char *in_ac_att_name)
{
    short *value = (short *)calloc(i_att_len, sizeof(short));
    int32_t ec = nc_get_att_short(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_short(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, NC_SHORT, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy an int attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_int(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                        variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                        int32_t i_att_len, char *in_ac_att_name)
{
    int32_t *value = (int32_t *)calloc(i_att_len, sizeof(int32_t));
    int32_t ec = nc_get_att_int(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_int(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, NC_INT, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy a float attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_float(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                          variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                          int32_t i_att_len, char *in_ac_att_name)
{
    float *value = (float *)calloc(i_att_len, sizeof(float));
    int32_t ec = nc_get_att_float(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_float(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, NC_FLOAT, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy a double attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_double(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                           variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                           int32_t i_att_len, char *in_ac_att_name)
{
    double *value = (double *)calloc(i_att_len, sizeof(double));
    int32_t ec = nc_get_att_double(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_double(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, NC_DOUBLE, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy an ubyte attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_ubyte(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                          variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                          int32_t i_att_len, char *in_ac_att_name)
{
    unsigned char *value = (unsigned char *)calloc(i_att_len, sizeof(unsigned char));
    int32_t ec = nc_get_att_ubyte(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_ubyte(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, NC_UBYTE, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy an ushort attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_ushort(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                           variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                           int32_t i_att_len, char *in_ac_att_name)
{
    unsigned short *value = (unsigned short *)calloc(i_att_len, sizeof(unsigned short));
    int32_t ec = nc_get_att_ushort(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_ushort(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, NC_USHORT, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy an uint attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_uint(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                         variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                         int32_t i_att_len, char *in_ac_att_name)
{
    unsigned int *value = (unsigned int *)calloc(i_att_len, sizeof(unsigned int));
    int32_t ec = nc_get_att_uint(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_uint(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, NC_UINT, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy an int64 attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_int64(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                          variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                          int32_t i_att_len, char *in_ac_att_name)
{
    long long *value = (long long *)calloc(i_att_len, sizeof(long long));
    int32_t ec = nc_get_att_longlong(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_longlong(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, NC_INT64, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy an uint64 attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_uint64(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                           variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                           int32_t i_att_len, char *in_ac_att_name)
{
    unsigned long long *value = (unsigned long long *)calloc(i_att_len, sizeof(unsigned long long));
    int32_t ec = nc_get_att_ulonglong(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_ulonglong(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, NC_UINT64, i_att_len, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy a string attribute from the input file to the output file
 * @param in_s_file_input The input file information
 * @param in_s_file_output The output file information
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @param i_att_len The length of the attribute
 * @param in_ac_att_name The name of the attribute
 * @return <b>void</b>
 */
void copy_attribute_string(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
                           variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
                           int32_t i_att_len, char *in_ac_att_name)
{
    char **value = (char **)calloc(i_att_len, sizeof(char *));

    int32_t ec = nc_get_att_string(in_s_file_input.i_file_id, in_s_ref_var.i_id, in_ac_att_name, value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Get attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_input.ac_path, in_s_ref_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    ec = nc_put_att_string(in_s_file_output.i_file_id, in_s_fill_var.i_id, in_ac_att_name, i_att_len, (const char **)value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Set attribute:" RESET RED " %s: %s: %s: %s\n" RESET, 
        in_s_file_output.ac_path, in_s_fill_var.ac_var_name, in_ac_att_name, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    free(value);
}

/**
 * @brief Copy the attributes from the input file to the output file
 * @param in_i_input_file The index of the input file
 * @param in_s_ref_var The variable information of the input file
 * @param in_s_fill_var The variable information of the output file
 * @return <b>void</b>
 */
void assembler::copy_attributes(int32_t in_i_input_file, variable_information_t & in_s_ref_var,
                                variable_information_t & in_s_fill_var)
{
    static void (*copy_attribute[])(file_information_t & in_s_file_input, file_information_t & in_s_file_output,
        variable_information_t & in_s_ref_var, variable_information_t & in_s_fill_var,
        int32_t i_att_len, char *in_ac_att_name) = {
        &copy_attribute_invalid, &copy_attribute_byte, &copy_attribute_char, &copy_attribute_short,
        &copy_attribute_int, &copy_attribute_float, &copy_attribute_double,
        &copy_attribute_ubyte, &copy_attribute_ushort, &copy_attribute_uint,
        &copy_attribute_int64, &copy_attribute_uint64, &copy_attribute_string};
        int32_t ec = 0;

    for (int32_t i_index_attributes = 0; i_index_attributes < in_s_ref_var.i_natts; i_index_attributes++) {
        char ac_att_name[NC_MAX_NAME + 1];
        nc_type type = 0;
        size_t i_att_len = 0;

        ec = nc_inq_attname(_vs_input_files[in_i_input_file].i_file_id, in_s_ref_var.i_id, i_index_attributes, ac_att_name);
        if (ec != 0) {
            DEBUG;
            fprintf(stderr, RED BOLD "Get attribute name:" RESET RED " %s: %s: id = %d: %s\n" RESET, 
            _vs_input_files[in_i_input_file].ac_path, in_s_ref_var.ac_var_name, i_index_attributes, nc_strerror(ec));
            std::exit(EXIT_FAILURE);
        }
        ec = nc_inq_att(_vs_input_files[in_i_input_file].i_file_id, in_s_ref_var.i_id, ac_att_name, &type, &i_att_len);
        if (ec != 0) {
            DEBUG;
            fprintf(stderr, RED BOLD "Get attribute information:" RESET RED " %s: %s: %s: %s\n" RESET,
            _vs_input_files[in_i_input_file].ac_path, in_s_ref_var.ac_var_name, ac_att_name, nc_strerror(ec));
            std::exit(EXIT_FAILURE);
        }
        if (type < 0 || type > 12)
            type = 0;
        copy_attribute[type](_vs_input_files[in_i_input_file], _s_output_file, in_s_ref_var, in_s_fill_var, i_att_len, ac_att_name);
    }
}

/**
 * @brief Add the global attributes to the output file
 * and copy globals attributes from first input file
 * @return <b>void</b>
 */
void assembler::add_globals_attributes(void)
{
    const char *ac_value = "This file was generated by netcdf-assembler from several NetCDF or GRIB files.";
    int32_t ec = nc_put_att_text(_s_output_file.i_file_id,
        NC_GLOBAL, "File description", strlen(ac_value), ac_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Add global attribute:" RESET RED " File description: %s\n" RESET, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }    
    std::string str_tmp_value = "";
    for (size_t i_index_file = 0; i_index_file < _vs_input_files.size(); i_index_file++) {
        if (i_index_file != 0)
            str_tmp_value += ", ";
        str_tmp_value += _vs_input_files[i_index_file].ac_path;
    }
    ac_value = (char *)str_tmp_value.c_str();
    ec = nc_put_att_text(_s_output_file.i_file_id,
        NC_GLOBAL, "Files list", strlen(ac_value), ac_value);
    if (ec != 0) {
        DEBUG;
        fprintf(stderr, RED BOLD "Add global attribute:" RESET RED " File description: %s\n" RESET, nc_strerror(ec));
        std::exit(EXIT_FAILURE);
    }
    variable_information_t s_ref_global_attributes = {0};
    variable_information_t s_fill_global_attributes = {0};
    strcpy(s_ref_global_attributes.ac_var_name, "Global attributes");
    strcpy(s_fill_global_attributes.ac_var_name, "Global attributes");
    s_ref_global_attributes.i_id = NC_GLOBAL;
    s_fill_global_attributes.i_id = NC_GLOBAL;
    s_ref_global_attributes.i_natts = _vs_input_files[0].i_nb_attributes;
    copy_attributes(0, s_ref_global_attributes, s_fill_global_attributes);
}
