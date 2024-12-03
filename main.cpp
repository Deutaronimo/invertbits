#include<iostream>
#include<fstream>


using namespace std;

int main(int argc, char *argv[])
{
    //int position = 0x3;
    char byte;
    bool invertBytes = true;
    string help = "help";
    string helpUpper = "HELP";
    string fileSaved = "";
    string defaultedFilename = "inverted.txt";

    ifstream infile;
    ofstream outfile;

    if (argv[1] == NULL )
    {
        cout << "No arguments given, run invertbits help for information.\n";
        return 1;
    }

    if (argv[1] == help || argv[1] == (helpUpper))
    {
        cout << "syntax: invertbits INPUT.file OUTPUT.file\n";
        cout << "if OUTPUT name isn't given, inverted.txt will be used\n";
        cout << "_________________________________________\n";
        cout << "This is a simple BIT inversion of all the bytes in a given file.\n";
        cout << "VER:1.0    07/03/2024";
        cout << "By J.G.V.\n";
        return 0;
    }

    if (argv[2] == NULL)
    {
        fileSaved = defaultedFilename;
    }

    else
    {
        fileSaved = argv[2];
    }

    string fileName  = argv[1];

    infile.open (fileName, ios::binary|ios::in);

    // Some error checking.
    if (infile.fail())
    {
        cout << "____________________________________________________\n";
        cout << "Try arguments: invertbits [input.file] [output.file]\n";
        cout << "Error file not found, Exiting.\n";
        return 1;
    }

    outfile.open(fileSaved, ios::binary|ios::out);

    cout << "Loaded file: " << argv[1] << endl;
    
    // Get file size and create a buffer on the heap.
    infile.seekg(0,ios_base::end);
    int filesize = infile.tellg();
    char *fileBuffer = new char[filesize];

    // Set file pointer to start of file and copy it to the buffer
    infile.seekg(ios_base::beg);
    infile.read(fileBuffer,filesize);
    
    if (invertBytes)
    {
        for (int x = 0; x < filesize; ++x)
        {
            // invert the file bytes.
            byte = 0xff - fileBuffer[x];
            outfile << byte;
        }        

    }

    else    
    {
        for (int x = 0; x < filesize; ++x)
        {
            // invert the file bytes.
            outfile << fileBuffer[x];
        }

    }
    
    // Some output.
    cout << "Copied " <<  filesize << " Bytes to buffer then file." << endl;

    if (invertBytes)
    {
        cout << "Bytes were inverted and saved to " << fileSaved << endl;
    }

    else
    {
        cout << "Buffer saved to  " << fileSaved << endl;
    }   
    
    // Clean up.
    delete[] fileBuffer;
    infile.close();
    outfile.close();

    cout << "All ok.." << endl;
   
    return 0;
}