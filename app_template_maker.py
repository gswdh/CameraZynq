class AppTemplate:
    name = ""

    def __init__(self, name, cps_pipe=False):
        self.name = name
        self.cps_pipe = cps_pipe

    def includes(self) -> str:
        text = ""

        # App header
        text += f'#include "{self.name.lower()}.h"\n'
        text += "\n"

        # Apps config header
        text += "// App configuration\n"
        text += '#include "apps_config.h"\n'
        text += "\n"

        # FreeRTOS headers
        text += "// FreeRTOS\n"
        text += '#include "freertos/FreeRTOS.h"\n'
        text += '#include "freertos/task.h"\n'
        text += '#include "freertos/timers.h"\n'
        text += "\n"

        # Drivers
        text += "// Driver includes\n"
        text += "\n"

        # Logging
        text += "// Logging\n"
        text += "\n"

        # pubsub
        if self.cps_pipe:
            text += "// cpubsub\n"
            text += '#include "cpubsub.h"\n'
            text += '#include "messages.h"\n'
            text += "\n"

        # C libs
        text += "// C Libs\n"
        text += "#include <stdint.h>\n"
        text += "#include <stdbool.h>\n"
        text += "#include <assert.h>\n"
        if self.cps_pipe:
            text += "#include <stdlib.h>\n"
        text += "\n"

        # pubsub
        text += "// Logging meta\n"
        text += f'#define LOG_TAG "{self.name.upper()}"\n'
        text += "\n"

        return text

    def statics(self) -> str:
        text = ""

        text += f"static TimerHandle_t {self.name.lower()}_timer = NULL;\n"
        text += f"static TaskHandle_t {self.name.lower()}_task_handle = NULL;\n"
        text += "\n"

        # pubsub
        if self.cps_pipe:
            text += "static pipe_t pipe = {0};\n"
            text += "static uint8_t *msg_buffer = NULL;\n"
            text += "\n"
            text += f"static const uint32_t {self.name.lower()}_subs[] = {{0}};\n"
            text += "\n"

        return text

    def functions(self) -> str:
        text = ""

        text += f"static bool {self.name.lower()}_init(void)\n{{\n\treturn false;\n}}\n"
        text += "\n"

        text += f"static void {self.name.lower()}_task(void *params)\n{{\n\tvTaskDelete(NULL);\n}}\n"
        text += "\n"

        text += f'static void {self.name.lower()}_tick(TimerHandle_t timer)\n{{\n\txTaskCreate({self.name.lower()}_task, "{self.name.lower().replace("_", " ").title()} Task", {self.name.upper()}_STACK_DEPTH, NULL, {self.name.upper()}_TASK_PRIORITY, &{self.name.lower()}_task_handle);\n}}\n'
        text += "\n"

        text += f"void {self.name.lower()}_start(void * params)\n{{\n"
        if self.cps_pipe:
            text += "\t// Pipe length\n"
            text += f"\tpipe_set_length(&pipe, {self.name.upper()}_PIPE_LEN);\n"
            text += "\n\t// CPS subscriptions\n"
            text += f"\tfor(uint32_t i = 0; i < {self.name.upper()}_MIDS_CNT({self.name.lower()}_subs); i++)\n"
            text += "\t{\n"
            text += f"\t\tcps_subscribe({self.name.lower()}_subs[i], messages_msg_len({self.name.lower()}_subs[i]), &pipe);\n"
            text += "\t}\n"
            text += "\t\n"
            text += "\t// Make some space for RXd messages\n"
            text += "\tmsg_buffer = (uint8_t*)malloc((size_t)pipe_item_size(&pipe));\n"
            text += "\tif(msg_buffer == NULL)\n"
            text += "\t{\n"
            text += "\t\t// Error!\n"
            text += "\t}\n"
            text += "\n"
            text += "\telse\n"
            text += "\t{\n"

        if self.cps_pipe:
            text += "\t"
        text += f"\t// Perform the init routine\n"
        if self.cps_pipe:
            text += "\t"
        text += f"\tif({self.name.lower()}_init() == true)\n"
        if self.cps_pipe:
            text += "\t"
        text += "\t{\n"
        if self.cps_pipe:
            text += "\t"
        text += "\t\t// Create and start the app tick timer\n"
        if self.cps_pipe:
            text += "\t"
        text += f'\t\t{self.name.lower()}_timer = xTimerCreate("{self.name.lower().replace("_", " ").title()} Tick", pdMS_TO_TICKS({self.name.upper()}_INTERVAL_MS), pdTRUE, NULL, {self.name.lower()}_tick);\n'
        if self.cps_pipe:
            text += "\t"
        text += f"\t\txTimerStart({self.name.lower()}_timer, 0);\n"
        if self.cps_pipe:
            text += "\t"
        text += "\t}\n"
        if self.cps_pipe:
            text += "\t}\n"
        text += "\n\tvTaskDelete(NULL);\n"

        text += "}\n\n"

        text += f"void {self.name.lower()}_stop(void)\n{{\n\txTimerStop({self.name.lower()}_timer, 0);\n\txTimerDelete({self.name.lower()}_timer, 0);\n\n"

        text += f"\tvTaskDelete({self.name.lower()}_task_handle);\n"
        if self.cps_pipe:
            text += "\tif(msg_buffer != NULL)\n"
            text += "\t{\n"
            text += "\t\tfree(msg_buffer);\n"
            text += "\t}\n"

        text += "}\n"
        text += "\n"

        return text

    def header(self) -> str:
        text = ""

        text += "#pragma once\n"
        text += "\n"

        text += f"// {self.name.lower().replace('_', ' ').title()} App Configuration\n"
        text += f"#define {self.name.upper()}_INTERVAL_MS (100)\n"
        text += f"#define {self.name.upper()}_STACK_DEPTH (1024)\n"
        text += f"#define {self.name.upper()}_TASK_PRIORITY (tskIDLE_PRIORITY)\n"

        if self.cps_pipe:
            text += f"#define {self.name.upper()}_PIPE_LEN (8)\n"
            text += "\n"
            text += (
                f"#define {self.name.upper()}_MIDS_CNT(a) (sizeof(a) / sizeof(a[0]))\n"
            )

        text += "\n"
        text += f"void {self.name.lower()}_start(void * params);\n"
        text += f"void {self.name.lower()}_stop(void);\n"
        text += "\n"

        return text

    def generate(self) -> str:
        assert self.name != "", "No app name"

        source = ""
        source += self.includes()
        source += self.statics()
        source += self.functions()

        header = ""
        header += self.header()

        return header, source

    def output(self, directory) -> None:
        header, source = self.generate()
        with open(f"{directory}/{self.name.lower()}.h", "w") as f:
            f.write(header)
        with open(f"{directory}/{self.name.lower()}.c", "w") as f:
            f.write(source)
