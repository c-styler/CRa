/*
 * scanner.c
 * Created on Fri Aug 14 2026
 * Part of C-Ra — SPDX-License-Identifier: MIT
 * Copyright (c) 2026 Omar Eltayeb
 */

#include "scanner.h"
#include "common.h"

#include <string.h>

static bool at_end(Scanner* scanner)
{
    return *scanner->current == '\0';
}

static Token make_token(Scanner* scanner, TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner->start;
    token.length = (int)(scanner->current - scanner->start);
    token.line = scanner->line;

    return token;
}

static Token error_token(Scanner* scanner, const char* message)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = strlen(message);
    token.line = scanner->line;

    return token;
}

static char advance(Scanner* scanner)
{
    scanner->current++;
    return scanner->current[-1];
}

static bool match(Scanner* scanner, char expected)
{
    if (at_end(scanner))
        return false;

    if (*scanner->current == expected)
    {
        scanner->current++;
        return true;
    }

    return false;
}

static char peek(Scanner* scanner)
{
    return scanner->current[0];
}

static char peek_next(Scanner* scanner)
{
    if (at_end(scanner))
        return '\0';
    return scanner->current[1];
}

static int length(Scanner* scanner)
{
    return (int)(scanner->current - scanner->start);
}

void scanner_init(Scanner* scanner, const char* source)
{
    scanner->start = source;
    scanner->current = source;
    scanner->line = 1;
}

static void skip_whitespace(Scanner* scanner)
{
    while (true)
    {
        char c = peek(scanner);
        switch (c)
        {
        case ' ':
        case '\t':
        case '\r':
        {
            advance(scanner);
        }
        break;

        case '\n':
        {
            scanner->line++;
            advance(scanner);
            break;
        }
        break;

        case '/':
        {
            if (peek_next(scanner) == '/')
            {
                while (peek(scanner) != '\n' && !at_end(scanner))
                {
                    advance(scanner);
                }
            }
            else
            {
                return;
            }
        }
        break;

        default:
            return;
        }
    }
}

static Token make_string(Scanner* scanner)
{
    while (peek(scanner) != '"' && !at_end(scanner))
    {
        if (peek(scanner) == '\n')
        {
            scanner->line++;
        }

        advance(scanner);
    }

    if (at_end(scanner))
        return error_token(scanner, "Unterminated String");

    advance(scanner);
    return make_token(scanner, TOKEN_STRING);
}

static bool is_digit(char c)
{
    return (c >= '0') && (c <= '9');
}

static Token make_number(Scanner* scanner)
{
    while (is_digit(peek(scanner)))
        advance(scanner);

    bool decimal = false;
    if (peek(scanner) == '.' && is_digit(peek_next(scanner)))
    {
        decimal = true;
        advance(scanner);

        while (is_digit(peek(scanner)))
            advance(scanner);
    }

    if (decimal)
    {
        return make_token(scanner, TOKEN_FLOAT);
    }

    return make_token(scanner, TOKEN_INT);
}

static bool is_alpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

/*
 * rest : string containing the rest of the keyword (after *start*)
 */
static TokenType check_keyword(Scanner* scanner, int start, int length,
                               const char* rest, TokenType type)
{
    bool length_match =
        (scanner->current - scanner->start) == (start + length);
    if (length_match &&
        memcmp(scanner->start + start, rest, length) == 0)
    {
        return type;
    }

    return TOKEN_IDENTIFIER;
}

static TokenType identifier_type(Scanner* scanner)
{
    switch (scanner->start[0])
    {
    case 'a':
        return check_keyword(scanner, 1, 2, "nd", TOKEN_AND);
    case 'e':
        return check_keyword(scanner, 1, 3, "lse", TOKEN_ELSE);
    case 'f':
    {
        if (length(scanner) > 1)
        {
            switch (scanner->start[1])
            {
            case 'a':
                return check_keyword(scanner, 2, 3, "lse", TOKEN_FALSE);
            case 'o':
                return check_keyword(scanner, 2, 1, "r", TOKEN_FOR);
            }
        }
    }
    break;
    case 'i':
        return check_keyword(scanner, 1, 1, "f", TOKEN_IF);

    case 'o':
        return check_keyword(scanner, 1, 1, "r", TOKEN_OR);

    case 'r':
        return check_keyword(scanner, 1, 5, "eturn", TOKEN_RETURN);

    case 't':
        return check_keyword(scanner, 1, 3, "rue", TOKEN_TRUE);

    case 'w':
        return check_keyword(scanner, 1, 4, "hile", TOKEN_WHILE);

    case 'p':
        return check_keyword(scanner, 1, 8, "rocedure",
                             TOKEN_PROCEDURE);
    case 's':
        return check_keyword(scanner, 1, 5, "truct", TOKEN_STRUCT);
    }

    return TOKEN_IDENTIFIER;
}

static Token make_identifier(Scanner* scanner)
{
    while (is_alpha(peek(scanner)) || is_digit(peek(scanner)))
        advance(scanner);

    return make_token(scanner, identifier_type(scanner));
}

Token scanner_scan_token(Scanner* scanner)
{
    skip_whitespace(scanner);
    scanner->start = scanner->current;
    if (at_end(scanner))
    {
        return make_token(scanner, TOKEN_EOF);
    }

    char c = advance(scanner);

    if (is_digit(c))
    {
        return make_number(scanner);
    }
    if (is_alpha(c))
    {
        return make_identifier(scanner);
    }

    switch (c)
    {
    case '(':
        return make_token(scanner, TOKEN_LEFT_PAREN);
    case ')':
        return make_token(scanner, TOKEN_RIGHT_PAREN);
    case '{':
        return make_token(scanner, TOKEN_LEFT_BRACE);
    case '}':
        return make_token(scanner, TOKEN_RIGHT_BRACE);
    case ';':
        return make_token(scanner, TOKEN_SEMICOLON);
    case ',':
        return make_token(scanner, TOKEN_COMMA);
    case '.':
        return make_token(scanner, TOKEN_DOT);
    case '-':
        return make_token(scanner, TOKEN_MINUS);
    case '+':
        return make_token(scanner, TOKEN_PLUS);
    case '/':
        return make_token(scanner, TOKEN_SLASH);
    case '*':
        return make_token(scanner, TOKEN_STAR);

    case '!':
        return make_token(scanner, match(scanner, '=')
                                       ? TOKEN_BANG_EQUAL
                                       : TOKEN_BANG);
    case '=':
        return make_token(scanner, match(scanner, '=')
                                       ? TOKEN_EQUAL_EQUAL
                                       : TOKEN_EQUAL);
    case '<':
        return make_token(scanner, match(scanner, '=')
                                       ? TOKEN_LESS_EQUAL
                                       : TOKEN_LESS);
    case '>':
        return make_token(scanner, match(scanner, '=')
                                       ? TOKEN_GREATER_EQUAL
                                       : TOKEN_LESS);

    case '"':
        return make_string(scanner);
    }

    return error_token(scanner, "Unexpected Character");
}
