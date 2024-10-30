/*
** SEAGNAL PROJECT, 2024
** netcdf-assembler
** File description:
** The main file of the project
*/
/**
 * @file main.cc
 * @brief The main file of the project
 * @author Nicolas TORO
 */

#include "../include/nc_assembler.hh"

/**
 * @brief Check if there is an error
 * @param in_i_error The error code
 * @param in_ac_file The file name
 * @param in_i_line The line number
 * @param in_ac_func The function name
 * @return <b>void</b>
 */
void check_error(int in_i_error, const char *in_ac_file,
                 const int in_i_line, const char *in_ac_func)
{
    if (in_i_error != 0) {
        #ifdef DEBUG_MODE
        std::cerr << RED BOLD "ERROR: " RESET RED << in_ac_file << ":" << in_i_line << ": " << in_ac_func << RESET << std::endl;
        #endif
        std::cerr << RED BOLD "Error information: " RESET RED << nc_strerror(in_i_error) << RESET << std::endl;
        std::exit(EXIT_FAILURE);
    }
}

/**
 * @brief Display the help message
 * @param argv The program arguments
 * @return <b>void</b>
 */
void display_help(char **argv)
{
    std::cout << BOLD "Usage: " RESET << argv[0] << " output_file files" << std::endl << std::endl;
    std::cout << BOLD UNDERLINE "DESCRIPTION" RESET << std::endl;
    std::cout << "\tAssembles multiple NetCDF (and GRIB) files into one large NetCDF file." << std::endl;
    std::exit(EXIT_FAILURE);
}

/**
 * @brief The assembler class constructor
 */
assembler::assembler(int argc, char **argv)
{
    if (argc < 3)
        display_help(argv);
    for (int32_t i_input_index = 2; i_input_index < argc; i_input_index++) {
        file_information_t s_input_file = {0};
        s_input_file.ac_path = argv[i_input_index];
        open_file(s_input_file, NC_NOWRITE);
        get_info(s_input_file);
        _vs_input_files.push_back(s_input_file);
    }
    _s_output_file.ac_path = argv[1];
    create_file(_s_output_file, NC_NETCDF4);
    get_info(_s_output_file);
    std::cout << "Created output file: " << _s_output_file.ac_path << std::endl;
}

/**
 * @brief The assembler class destructor
 */
assembler::~assembler()
{
    for (size_t i_input_index = 0; i_input_index < _vs_input_files.size(); i_input_index++)
        close_file(_vs_input_files[i_input_index]);
    close_file(_s_output_file);
    std::cout << "Assembler clean." << std::endl;
}

int main(int argc, char **argv)
{
    assembler c_assembler(argc, argv);

    c_assembler.add_globals_attributes();
    c_assembler.copy_dimensions();
    c_assembler.copy_variables();
}
