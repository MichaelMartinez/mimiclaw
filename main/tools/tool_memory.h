#pragma once

#include "esp_err.h"
#include <stddef.h>

/**
 * Write/append to long-term memory (MEMORY.md).
 * Input JSON: {"content": "..."}
 */
esp_err_t tool_memory_write_execute(const char *input_json, char *output, size_t output_size);

/**
 * Append a note to today's daily memory file.
 * Input JSON: {"content": "..."}
 */
esp_err_t tool_daily_note_execute(const char *input_json, char *output, size_t output_size);
