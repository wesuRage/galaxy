#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "frontend/parser/core.h"
#include "frontend/parser/types/parse_type.h"

char* check_and_append_array(Parser *parser, const char* base_type) {
    if (current_token(parser).type == TOKEN_OBRACKET) {
        consume_token(parser);

        if (current_token(parser).type == TOKEN_CBRACKET) {
            consume_token(parser);
            size_t len = strlen(base_type) + 3;
            char* array_type = malloc(len);
            snprintf(array_type, len, "%s[]", base_type);
            return array_type;
        }

        char *num = expect(parser, TOKEN_NUMBER, "Expected number").lexeme;
        if (current_token(parser).type == TOKEN_CBRACKET) {
            consume_token(parser);
            size_t len = strlen(base_type) + strlen(num) + 3;
            char* array_type = malloc(len);
            snprintf(array_type, len, "%s[%s]", base_type, num);
            return array_type;
        }
    }
    return strdup(base_type);
}

char* parse_generic_type(Parser *parser, const char* base_type) {
    consume_token(parser);
    size_t capacity = 128;
    size_t length = strlen(base_type) + 1;
    char* result = malloc(capacity);
    strcpy(result, base_type);
    strcat(result, "<");

    char* sub_type = parse_type(parser);
    length += strlen(sub_type) + 1;
    if (length >= capacity) {
        capacity *= 2;
        result = realloc(result, capacity);
    }
    strcat(result, sub_type);

    while (current_token(parser).type == TOKEN_COMMA) {
        consume_token(parser);
        strcat(result, ",");
        char* next_type = parse_type(parser);
        length += strlen(next_type) + 1;
        if (length >= capacity) {
            capacity *= 2;
            result = realloc(result, capacity);
        }
        strcat(result, next_type);
    }

    printf("token: %s\n", current_token(parser).lexeme);

    expect(parser, TOKEN_GT, "Expected \">\".");
    strcat(result, ">");
    return result;
}

char* parse_type(Parser *parser) {
    switch (current_token(parser).type) {
        case TOKEN_TYPE_I8: 
            consume_token(parser); 
            return check_and_append_array(parser, "i8");

        case TOKEN_TYPE_I16: 
            consume_token(parser); 
            return check_and_append_array(parser, "i16");

        case TOKEN_TYPE_I32: 
            consume_token(parser); 
            return check_and_append_array(parser, "i32");

        case TOKEN_TYPE_I64: 
            consume_token(parser); 
            return check_and_append_array(parser, "i64");

        case TOKEN_TYPE_I128: 
            consume_token(parser); 
            return check_and_append_array(parser, "i128");

        case TOKEN_TYPE_U8: 
            consume_token(parser); 
            return check_and_append_array(parser, "u8");

        case TOKEN_TYPE_U16: 
            consume_token(parser); 
            return check_and_append_array(parser, "u16");

        case TOKEN_TYPE_U32: 
            consume_token(parser); 
            return check_and_append_array(parser, "u32");

        case TOKEN_TYPE_U64: 
            consume_token(parser); 
            return check_and_append_array(parser, "u64");

        case TOKEN_TYPE_U128: 
            consume_token(parser); 
            return check_and_append_array(parser, "u128");

        case TOKEN_TYPE_ISIZE: 
            consume_token(parser); 
            return check_and_append_array(parser, "isize");

        case TOKEN_TYPE_USIZE: 
            consume_token(parser); 
            return check_and_append_array(parser, "usize");

        case TOKEN_TYPE_F32: 
            consume_token(parser); 
            return check_and_append_array(parser, "f32");

        case TOKEN_TYPE_F64: 
            consume_token(parser); 
            return check_and_append_array(parser, "f64");

        case TOKEN_TYPE_BOOL: 
            consume_token(parser); 
            return check_and_append_array(parser, "bool");

        case TOKEN_TYPE_VOID: 
            consume_token(parser); 
            return strdup("void");

        case TOKEN_TYPE_NULL: 
            consume_token(parser); 
            return strdup("null");

        case TOKEN_TYPE_UNDEFINED: 
            consume_token(parser); 
            return strdup("undefined");

        case TOKEN_TYPE_STRING: 
            consume_token(parser); 
            return check_and_append_array(parser, "string");

        case TOKEN_TYPE_ARRAY: 
            consume_token(parser); 
            expect(parser, TOKEN_LT, "Expected \"<\".");
            return parse_generic_type(parser, "array");

        case TOKEN_TYPE_SLICE: 
            consume_token(parser); 
            expect(parser, TOKEN_LT, "Expected \"<\".");
            return parse_generic_type(parser, "slice");

        case TOKEN_IDENTIFIER: {
            char* identifier = strdup(consume_token(parser).lexeme);
            if (current_token(parser).type == TOKEN_LT) {
                char* generic_type = parse_generic_type(parser, identifier);
                free(identifier);
                return generic_type;
            }
            return check_and_append_array(parser, identifier);
        }

        default:
            return "implicit";
    }
}