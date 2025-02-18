#include <iostream>
using namespace std;

class TextFile
{
    public:
        string text = "";

        TextFile() { }

        TextFile(string fileContents) { text = fileContents;}

        TextFile(TextFile &t) { this->text = t.text;}
};

class Action
{
    public:
        virtual void perform(TextFile &t) = 0;

};

class Write : public Action
{
    private:
        string* toWrite;

    public:
        void perform(TextFile &t) override
        {
            t.text.append(*toWrite);
        }
        Write(string whatToWrite)
        {
            toWrite = new string(whatToWrite);
        }

};

struct ActionStack
{
    Action* actionList[3];
    int count = 0;

    void push(Action* action,TextFile &t)
    {
        switch (count)
        {
        case 0:
            actionList[0] = action;
            ++count;
            break;

        case 1:
            /* code */
            actionList[1] = action;
            ++count;
            break;

        case 2:
            /* code */
            actionList[2] = action;
            ++count;
            break;

        case 3:
            actionList[0]->perform(t);
            delete actionList[0];
            actionList[0] = actionList[1];
            actionList[1] = actionList[2];
            actionList[2] = action;
            --count;
            break;
        
        default:
            break;
        }

    }

    void applyAll(TextFile &t)
    {
        for (int i = 0; i < count; i++)
        {
            actionList[i]->perform(t);
        }
    }

    void pop() //undo
    {
        switch (count)
        {
        case 0:
            return;
            break;

        case 1:
            /* code */
            delete actionList[1];
            actionList[1] = nullptr;
            --count;
            break;

        case 2:
            /* code */
            delete actionList[2];
            actionList[2] = nullptr;
            --count;
            break;

        case 3:
            delete actionList[3];
            actionList[3] = nullptr;
            --count;
            break;
        
        default:
            break;
        }

    }
};

class Editor
{
    private:
        TextFile textFile;
        ActionStack actionStack;


    public:
        Editor(TextFile textFile)
        {
            this->textFile = textFile;
        }

        void write(string text)
        {
            Write *w = new Write(text);
            Action* a = w;
            actionStack.push(a, textFile);
        }

        void undo()
        {
            actionStack.pop();
        }

        void print()
        {
            TextFile temp = textFile;
            actionStack.applyAll(temp);

            cout << temp.text << endl ;
        }
};

int main()
{
    TextFile textFile("Hello");

    Editor editor(textFile);
    editor.print();
    
    editor.write(" world");
    editor.print();
    
    editor.write("!");
    editor.print();

    //editor.write(" This");
    //editor.print();

    //editor.write(" is a Text Editor!");
    //editor.print();

    editor.undo();
    editor.print();
}