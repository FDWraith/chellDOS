# chellDOS
    by Kevin Zhang and Tina La

    Features:
        Executes commands like bash!
        Redirection using >, <, >>, 2>
        Piping
        
    Attempted:
        Tried to get triple piping working, but the solution we have is too hard to implement.
        
    Bugs:
        Exit may have to be inputted more than once to actually exit.
        The prompt symbol ">" may appear as ">>>" after running certain commands.
        Sometimes, umask does not work as intended.
    
    Files & Function Headers:
    
    parse.c
        Handles all line parsing fucntions
        
        /*======== char * * * parseInput(char * string) ==========
        Inputs:  char * string
        Returns: An array of commands

        Uses parseLine to parse commands from stdin. 
        Can parse single and multiple commands.
        ====================*/
        
        /*======== char * * parseLine( char * string ) ==========
        Inputs:  char * string
        Returns: An array made up of parsed string

        Uses strsep to parse the string on " " and 
        create an array that is usable by execvp.
        ====================*/
        
    execute.c
        Handles execution of commands.
        
        /*======== int executeLine(char * * cmd) ==========
        Inputs:  char * * cmd
        Returns: pid of child process

        Handles execution of a single line command. Executes simple commands, redirects
        execution of special commands to executeSpecialChar.
        ====================*/
        
        /*======== int executeSpecialChar(char * * cmd, char * target) ==========
        Inputs:  char * * cmd, char * target
        Returns: 1 if execution was successful, 0 if unsuccessful.

        Handles execution of a special single line commands such as redirection and piping.
        ====================*/
        
        /*======== int openSpecialChar(char * target , char * path) ==========
        Inputs:  char * target , char * path
        Returns: file descriptor of opened file

        Handles opening of files for redirection commands.
        ====================*/
        
        /*======== void executeList(char * * * cmdList) ==========
        Inputs:  char * * * cmdList
        Returns: void, no return value

        General function for executing commands, handles single and multiple commands.
        ====================*/