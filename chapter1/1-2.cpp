int main()
{
	return -1;
}

/*
using echo $? in linux shell to see the return value of this program
in linux returns 255 respects that exit out of range
-----------------------------------------------------------------------
In linux:

Out of range exit values can result in unexpected exit codes. 
An exit value greater than 255 returns an exit code modulo 256. 
For example, exit 3809 gives an exit code of 225 (3809 % 256 = 225)
*/