__kernel void hello(__global char* string)
{
    string[0] = 'H';
    string[1] = 'E';
    string[2] = 'L';
    string[3] = 'L';
    string[4] = 'O';
    string[5] = '-';
    string[6] = 'O';
    string[7] = 'P';
    string[8] = 'E';
    string[9] = 'N';
    string[10] = 'C';
    string[11] = 'L';
    string[12] = '\0';
}
