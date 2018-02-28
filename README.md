# CSE 31: Computer Assembly and Organization
Restrictive Grep (rgrep) written for my CSE31 class at UC Merced, implemented in C++.

## About
The project implementation is grep, a search function commonly found in UNIX-based operating systems, but is restrictive with a set of wildcard characters that can be within the pattern (the search term). These include:
- . (period) Matches any character.
- \+ (plus) The preceding character will appear one or more times
- ? (question) The preceding character may or may not appear in the line
- \\ (backslash) "Escapes" the following character, nullifying any special characteristics
