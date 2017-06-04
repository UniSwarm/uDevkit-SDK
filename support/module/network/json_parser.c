/**
 * @file json.c
 * @author Charles-Antoine NOURY (charlybigoud)
 * @copyright Robotips 2017
 *
 * @date June 4, 2017, 11:15 AM
 *
 * @brief JSON parsing protocol
 */

#include "json.h"

//get next field
// -> go through buffer until met a comma
void json_get_next_field(const JsonBuffer *json, char *name, char *value)
{
	int i = 0;
	while ( *(json->buffer.data + i) == ',')
	{

		++i;
	}

}










#ifdef TEST_JSON_PARSER
#include <stdio.h>
#include <string.h>
#include "../../sys/buffer.c"
#include "json_formater.c"

int main(void)
{
    JsonBuffer json;
    char data [500];
    // sprintf(data, "{\"name1\": \"value1\",\"name2\": \"42\",\"list1\": [\"name10\": \"value10\",\"name11\": \"value11\",\"name12\": \"value12\" ],\"obj1\": {\"name3\": \"42\",\"name4\": \"42\" },\"obj2\": {\"name5\": \"42\",\"name6\": \"42\" },\"list2\": [\"name20\": \"value20\",\"name21\": \"value21\",\"name22\": \"value22\" ] }");
    sprintf(data, "bonjour");
    printf("%s\n", data);

    json_init(&json, data, 500, JSON_MONOBLOC);
    printf("json.buffer.data_size: %ld", json.buffer.data_size);
    printf("%s\n", data);
    printf("%s\n", json.buffer.data);

    char data2 [500];
    sprintf(data2, "hello");
    printf("%s\n", data2);



	// json_get_next_field();

    return 0;
}

#endif // TEST_JSON_PARSER
