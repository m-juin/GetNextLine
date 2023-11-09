# # Get Next Line
<img alt="Get Next Line" src="https://img.shields.io/static/v1?label=Get Next Line&message=125+/+125&color=yellow&style=plastic"/>

# Project
Get Next Line is one of the three project in the 42 program second circle. It aims to introduce the students to 2 new concept of C language, the ***File Descriptor*** and the ***static variable*** by creating a function to read line by line a file.

# Contraint
According to the subject there is 3 contraint for this project:
*  The global variables are prohibited.
*  The *lseek* function is forbidden.
*  The whole files of the projects need to follow 42 norm ([Link](https://github.com/42School/norminette/blob/master/pdf/en.norm.pdf))

# External function(s) allowed
* read
* malloc
* free

# Behavior

## Argument(s)
* A int containing the fd of the file to read.

## Return
* The next readable line ended by a "*\n*" if that's not the last line of the file.
* if the next readable line is empty the function return NULL

# Bonus part
| Description | Mark |
|      --     |:----:|
| Use one or less static variable. | :white_check_mark: |
| Be able to read multiple ***File Descriptor*** at the same time. | :white_check_mark: |


# Usage

1. Include Get Next Line Header **"** ***get_next_line.h*** **"** in your main file
2. Print the return of the function.
3. Compile your files with:
    ```bash=
    cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 <files>.c
    ```
4. Launch the compiled program.

 ## Usage exemple
Here a simple main exemple
```clike=
#include "get_next_line.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int fd = open("testfile.txt", O_RDONLY);
	if (fd <= 2)
	{
		write(2, "No such file\n", 14);
		return 1;
	}
	char *buffer = NULL;
	buffer = get_next_line(fd);
	while (buffer != NULL)
	{
		printf("%s", buffer);
		free(buffer);
		buffer = get_next_line(fd);
	}
	close(fd);
}
```
