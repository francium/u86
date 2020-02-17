from u86_tokenizer import TokenType, Tokenizer, Token


SAMPLE_ASM = """\
mov r1 2
mov r2 3
mul r1 r2
hlt

foobar:
mov r1 [r1+3]
"""

EXPECTED_TOKEN_STREAM = [
    Token(TokenType.MNE, "mov", 1, 0),
    Token(TokenType.SPC, " ", 0, 0),
    Token(TokenType.ARG, "r1", 0, 0),
    Token(TokenType.SPC, " ", 0, 0),
    Token(TokenType.ARG, "2", 0, 0),
    Token(TokenType.LF, "\n", 0, 0),
    Token(TokenType.MNE, "mov", 0, 1),
    Token(TokenType.SPC, " ", 0, 1),
    Token(TokenType.ARG, "r2", 0, 1),
    Token(TokenType.SPC, " ", 0, 1),
    Token(TokenType.ARG, "3", 0, 1),
    Token(TokenType.LF, "\n", 0, 1),
    Token(TokenType.MNE, "mul", 0, 2),
    Token(TokenType.SPC, " ", 0, 2),
    Token(TokenType.ARG, "r1", 0, 2),
    Token(TokenType.SPC, " ", 0, 2),
    Token(TokenType.ARG, "r2", 0, 2),
    Token(TokenType.LF, "\n", 0, 2),
    Token(TokenType.MNE, "hlt", 0, 3),
    Token(TokenType.LF, "\n", 0, 3),
    Token(TokenType.LF, "\n", 0, 4),
    Token(TokenType.LABEL, "foobar", 0, 5),
    Token(TokenType.LF, "\n", 0, 5),
    Token(TokenType.MNE, "mov", 0, 6),
    Token(TokenType.SPC, " ", 0, 6),
    Token(TokenType.ARG, "r1", 0, 6),
    Token(TokenType.SPC, " ", 0, 6),
    Token(TokenType.ARG, "[r1+3]", 0, 6),
    Token(TokenType.LF, "\n", 0, 7),
    Token(TokenType.EOF, "", 0, 7),
]


def test_token_stream():
    tkzer = Tokenizer(SAMPLE_ASM)
    for expected, actual in zip(EXPECTED_TOKEN_STREAM, tkzer):
        assert expected == actual
