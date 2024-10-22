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

void f_display_help(char **argv)
{
    dprintf(1, "Usage: %s resolutions output files\n", argv[0]);
    std::exit(1);
}

assembler::assembler(int argc, char **argv)
{
    if (argc < 4)
        f_display_help(argv);
    try {
        _d_resolution = std::stof(argv[1]);
        std::cout << BOLD "Resolution: " RESET << _d_resolution << std::endl;
    } catch (const std::invalid_argument& ex) {
        fprintf(stderr, RED BOLD "Invalide resolution:" RESET RED " %s\n" RESET, argv[1]);
        std::exit(EXIT_FAILURE);
    }
    if (_d_resolution < 0) {
        fprintf(stderr, RED BOLD "Negative resolution:" RESET RED " %f\n" RESET, _d_resolution);
        std::exit(EXIT_FAILURE);
    }
    for (int32_t i_input_index = 3; i_input_index < argc; i_input_index++) {
        file_informations_t s_input_file = {0};
        s_input_file.ac_path = argv[i_input_index];
        f_open_file(s_input_file, NC_NOWRITE);
        f_get_infos(s_input_file);
        _vs_input_files.push_back(s_input_file);
    }
    _s_output_file.ac_path = argv[2];
    f_create_file(_s_output_file, NC_NETCDF4);
    f_get_infos(_s_output_file);
    std::cout << "Created output file: " << _s_output_file.ac_path << std::endl;
}

assembler::~assembler()
{
    for (size_t i_input_index = 0; i_input_index < _vs_input_files.size(); i_input_index++)
        f_close_file(_vs_input_files[i_input_index]);
    f_close_file(_s_output_file);
    std::cout << "Assembler clean." << std::endl;
}

int main(int argc, char **argv)
{
    assembler c_assembler(argc, argv);

    c_assembler.f_add_globals_attributes();
    c_assembler.f_copy_dimensions();
    c_assembler.f_copy_variables();
}
