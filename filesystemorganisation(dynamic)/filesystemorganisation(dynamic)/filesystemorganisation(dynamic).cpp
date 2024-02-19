#include <iostream>
#include <string>
#include <vector>
using namespace std;

// Node structure for the file system tree
struct Node {
    string name;
    bool isFile;
    vector<Node*> children;

    // Constructor to initialize a node with a name and type (file or directory)
    Node(string name, bool isFile) : name(name), isFile(isFile) {}
};

class FileSystem {
private:
    Node* root;

public:
    // Constructor to initialize the file system with the root directory
    FileSystem() {
        root = new Node("root", false);
    }

    // Function to create a new file or directory
    void create(string path, bool isFile) {
        Node* current = root;

        size_t pos = 0;
        while (pos < path.size()) {
            // Find the position of the next '/'
            size_t found = path.find('/', pos);
            // If '/' is not found, set it to the end of the path
            if (found == string::npos)
                found = path.size();

            // Extract the name of the directory/file
            string name = path.substr(pos, found - pos);

            Node* next = nullptr;
            // Check if the directory/file already exists
            for (Node* child : current->children) {
                if (child->name == name) {
                    next = child;
                    break;
                }
            }

            // If the directory/file does not exist, create it
            if (next == nullptr) {
                // If it's the last component of the path, set its type (file or directory)
                next = new Node(name, found == path.size() ? isFile : false);
                current->children.push_back(next);
            }

            current = next;
            pos = found + 1;
        }
    }

    // Function to display the file system structure
    void display() {
        displayHelper(root, 0);
    }

private:
    // Helper function to display the file system structure recursively
    void displayHelper(Node* node, int depth) {
        // Print indentation based on depth
        for (int i = 0; i < depth; ++i)
            cout << "  ";

        // Print the name and type (file or directory) of the current node
        if (node->isFile)
            cout << "- " << node->name << " (File)" << endl;
        else
            cout << "- " << node->name << " (Directory)" << endl;

        // Recursively display children nodes
        for (Node* child : node->children)
            displayHelper(child, depth + 1);
    }
};

int main() {
    // Create a file system object
    FileSystem fs;

    // Prompt user to create files/directories dynamically
    char choice;
    do {
        string path;
        cout << "Enter path to create (e.g., root/documents/file.txt): ";
        cin >> path;
        bool isFile;
        cout << "Is it a file? (0 for directory, 1 for file): ";
        cin >> isFile;

        // Create the file/directory
        fs.create(path, isFile);

        cout << "Do you want to create another file/directory? (y/n): ";
        cin >> choice;
    } while (choice == 'y' || choice == 'Y');

    // Display the file system structure
    cout << "\nFile System Structure:" << endl;
    fs.display();

    return 0;
}