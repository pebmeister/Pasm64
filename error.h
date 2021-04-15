#pragma once

// ***********************************************************************
// Author           : Paul Baxter
// Created          : 11-29-2015
//
// copyright (c) 2015 Paul Baxter
//
// Last Modified By : Paul
// Last Modified On : 11-29-2015
// ***********************************************************************

enum 
{
    error_outof_memory = 0,
    error_missing_output_file,
    error_output_file_specified_more_than_once,
    error_missing_symbol_file,
    error_symbol_file_specified_more_than_once,
    error_missing_log_file,
    error_log_file_specified_more_than_once,
    error_missing_list_file,
    error_list_file_specified_more_than_once,
    error_c64_output_format_specified_more_than_once,
    error_instruction_set_specified_more_than_once,
    error_illegal_opcodes_specified_more_than_once,
    error_no_input_file_specified,
    error_opening_log_file,
    error_opening_input_file,
    error_opening_symbol_file,
    error_opening_output_file,
    error_opening_list_file,
    error_creating_list_node,
    error_value_outof_range,
    error_missing_parameter,
    error_writing_list_file,
    error_reading_source_file,
    error_writing_output_file,
    error_invalid_opcode_mode,
    error_invalid_opcode_or_mode,
    error_source_string_null,
    error_unrecognized_escape_sequence,
    error_invalid_number_of_ops,
    error_invalid_parameters,
    error_for_reg_cant_be_nested,
    error_end_section_without_section,
    error_org_specified_more_than_once,
    error_adding_symbol,
    error_initializing_variable,
    error_infinite_loop_detected,
    error_expected_next,
    error_divide_by_zero,
    error_unknown_operator_type,
    error_unknown_node_type,
    error_symbol_reassignment,
    error_macro_parameter_not_found,
    error_macro_parameter_under_flow,
    error_no_warning_specified_more_than_once,
    error_branch_outof_range,
    error_program_counter_out_of_range,
    error_missing_end_section,
    error_circular_symbol_definitions,
    error_include_file_stack_overflow,
    error_cant_open_include_file
};

extern void Error(const char* module, int error);
extern void Warning(const char* module, int error);
extern void FatalError(const char* module, int error);
