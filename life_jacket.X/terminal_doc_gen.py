# This script generates documentation which can be seen in the dsp terminal.

class Command_doc:
    tag = ""
    cmd = ""
    doc = ""

    # @brief Creates a command documentation for one command
    # @param tag - The name of the C string constant
    # @param cmd - The command to create a Command_doc for
    # @param doc - The documentation text of the command
    def __init__(self, command_tag = "", command = "", documentation = ""):
        self.tag = command_tag
        self.cmd = command
        self.doc = documentation

class Cmd_parser:
    commands = []
    
    def parse_command_doc(self, filename = "terminal.c"):
        start_tag = "/*§"
        end_tag = "*/"
        
        with open(filename) as src_file:
            lines = src_file.readlines()

        parsing_doc = False
        parse_cmd = False
        doc = ""
        tag = ""
        cmd = ""
        for line in lines:
            if parse_cmd:
                parse_cmd = False
                end_of_tag = line.index('[')
                tag = line[len("static const char "):end_of_tag]
                start_of_cmd = line.index('"') + 1
                end_of_cmd = start_of_cmd + 1 + line[start_of_cmd + 1:].index('"')
                cmd = line[start_of_cmd:end_of_cmd]
                self.commands.append(Command_doc(tag, cmd, doc))

            if start_tag in line:
                parsing_doc = True
                doc = ""
                tag = ""
                cmd = ""
            elif parsing_doc and end_tag in line:
                parsing_doc = False
                parse_cmd = True
            elif parsing_doc:
                doc += line.strip() + "\\n\\r\\t"

    def create_help_function(self):
        with open("terminal_help.c", 'w') as f:
            print("/*", file=f)
            print("This file is an auto generated file.", file=f)
            print("Do not modify its contents manually!", file=f)
            print("*/", file=f)
            print("#include <string.h>", file=f)
            print("#include <stddef.h>", file=f)
            print("#include \"uart.h\"", file=f)

            print("void terminal_help(char* in)", file=f)
            print("{", file=f)

            first = True
            for cmd in self.commands:
                if first:
                    first = False
                    print("    if (NULL != strstr(in, \"" + cmd.cmd + "\"))", file=f)
                else:
                    print("    else if (NULL != strstr(in, \"" + cmd.cmd + "\"))", file=f)
                print("    {", file=f)
                print("        uart_write_string(\"\\t" + cmd.doc + "\\n\\r\");", file=f)
                print("        while (!uart_is_write_buffer_empty()){;}", file=f)
                print("    }", file=f)

            print("    else", file=f)
            print("    {", file=f)

            commands_list = []
            for cmd in self.commands:
                commands_list.append(cmd.cmd + "\\n\\r\\t")
            commands_list.sort()

            commands_string = '"\\t'
            for line in commands_list:
                commands_string += line
            commands_string += '"'

            print("        uart_write_string(\"\\tType \\\"help <command>\\\" for more info\\n\\r\");", file=f)
            print("        while (!uart_is_write_buffer_empty()){;}", file=f)
            print("        uart_write_string(\"\\tAvailible commands:\\n\\r\");", file=f)
            print("        while (!uart_is_write_buffer_empty()){;}", file=f)
            print("        uart_write_string(\"\\t------------------------------------\\n\\r\\t\");", file=f)
            print("        while (!uart_is_write_buffer_empty()){;}", file=f)
            
            for line in commands_list:
                print('        uart_write_string("' + line + '");', file=f)
                print("        while (!uart_is_write_buffer_empty()){;}", file=f)

            print("        uart_write_string(\"\\n\\r\");", file=f)
            print("    }", file=f)
            print("}", file=f)
            
            
# ===============================================================================
# Module test
# ===============================================================================

if __name__ == "__main__":
    print("Terminal doc gen started")
    parser = Cmd_parser()
    parser.parse_command_doc()
    parser.create_help_function()
    print("Terminal doc gen complete")
    
