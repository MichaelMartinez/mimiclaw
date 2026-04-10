#include "tool_memory.h"
#include "memory/memory_store.h"
#include "mimi_config.h"

#include <string.h>
#include "esp_log.h"
#include "cJSON.h"

static const char *TAG = "tool_memory";

esp_err_t tool_memory_write_execute(const char *input_json, char *output, size_t output_size)
{
    cJSON *root = cJSON_Parse(input_json);
    if (!root) {
        snprintf(output, output_size, "Error: invalid JSON input");
        return ESP_OK;
    }

    cJSON *content = cJSON_GetObjectItem(root, "content");
    if (!cJSON_IsString(content) || content->valuestring[0] == '\0') {
        cJSON_Delete(root);
        snprintf(output, output_size, "Error: 'content' field is required");
        return ESP_OK;
    }

    esp_err_t err = memory_write_long_term(content->valuestring);
    cJSON_Delete(root);

    if (err == ESP_OK) {
        snprintf(output, output_size, "Memory updated successfully (%d bytes written to MEMORY.md)",
                 (int)strlen(content->valuestring));
    } else {
        snprintf(output, output_size, "Error writing memory: %s", esp_err_to_name(err));
    }

    ESP_LOGI(TAG, "memory_write result: %s", output);
    return ESP_OK;
}

esp_err_t tool_daily_note_execute(const char *input_json, char *output, size_t output_size)
{
    cJSON *root = cJSON_Parse(input_json);
    if (!root) {
        snprintf(output, output_size, "Error: invalid JSON input");
        return ESP_OK;
    }

    cJSON *content = cJSON_GetObjectItem(root, "content");
    if (!cJSON_IsString(content) || content->valuestring[0] == '\0') {
        cJSON_Delete(root);
        snprintf(output, output_size, "Error: 'content' field is required");
        return ESP_OK;
    }

    esp_err_t err = memory_append_today(content->valuestring);
    cJSON_Delete(root);

    if (err == ESP_OK) {
        snprintf(output, output_size, "Daily note appended successfully (%d bytes)",
                 (int)strlen(content->valuestring));
    } else {
        snprintf(output, output_size, "Error appending daily note: %s", esp_err_to_name(err));
    }

    ESP_LOGI(TAG, "daily_note result: %s", output);
    return ESP_OK;
}
