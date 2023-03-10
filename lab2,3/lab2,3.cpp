#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include "myfunc.cpp"

//#include <vector>
#define VOID_INDEX -1

#define STD_SETW 8

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::setw;

using trash::cin_number;
using trash::text::spam;


class IL_Graf
{
private:
class Node;
typedef Node* pNode;
    class Node
    {
    public:
        pNode next;
        int data;
        Node()
        {    
            next = nullptr;
            data = -1;
        }
        Node(int data) : Node()
        {   
            this->data = data;
        }
        Node(pNode clone) 
        {
            this->data = clone->data;
            this->next = clone->next;
        }
        Node(int data, Node *next)
        {
            this->data = data;
            this->next = next;
        }
        ~Node()
        {    
            delete next;
        }
    };    

    void index_exception(size_t& index) 
    {
        if(index >= nodeCount)
            std::exception();
    }

    void del_last_node(size_t index)
    {
        if(this == nullptr)
            return;

        pNode tmp = nodeArray[index];
        if(tmp->next != nullptr)
        {
            while(tmp->next->next != nullptr)
                    tmp = tmp->next;
            
            delete tmp->next;
            tmp->next = nullptr;
        } else  
        {   
            delete nodeArray[index];
            nodeArray[index] = nullptr;   
        }
    }

    bool find_in_node(size_t index, int data) 
    {
        pNode tmp = nodeArray[index];
        while(tmp != nullptr)
            if(tmp->data == data)
                return true;
            else
                tmp = tmp->next;
        return false;
    }
    
    void add_last_node(size_t index, int data)
    {
        if(nodeArray[index] == nullptr)
        {
            nodeArray[index] = new Node;
            nodeArray[index]->data = data;
            return;
        }
        pNode tmp = nodeArray[index];
        while(tmp->next != nullptr)
            tmp = tmp->next;
        tmp->next = new Node;
        tmp->next->data = data;
    }  

    void unsafe_del_next_node(pNode tmp)//unsafe_del_next_node   PS: ?????????? ????????
    {
        pNode tmp_next = tmp->next->next;
        tmp->next->next = nullptr;
        delete tmp->next;
        tmp->next = tmp_next;
    }

    void del_node(size_t index, size_t search_data)
    {
        if(nodeArray[index]->next == nullptr)
        {
            if(nodeArray[index]->data == search_data)
            {
                delete nodeArray[index];
                nodeArray[index] = nullptr;
            }
            return;
        }

        pNode tmp = nodeArray[index];
        while(tmp->next != nullptr)
            if(tmp->next->data == search_data) 
            {
                unsafe_del_next_node(tmp);
            }
            else
                tmp = tmp->next;
    }

    void sort_and_del_reiteration_node(size_t index) //sort_and_del_reiteration_node
    {
        if(nodeArray[index] == nullptr)
            return;

        int buff;
        bool exit = false;
        pNode tmp = nodeArray[index];
        while(!exit)
        {
            tmp = nodeArray[index];
            exit = true;
            while(tmp->next != nullptr)
            {
                if(tmp->data > tmp->next->data) //???????? ????????????????????
                {
                    buff = tmp->data;
                    tmp->data = tmp->next->data;
                    tmp->next->data = buff;
                    exit = false;
                } else if(tmp->data == tmp->next->data)
                {
                    exit = false;
                    unsafe_del_next_node(tmp);
                    continue;
                }
                tmp = tmp->next;
            }
        }
    }

    int node_counter(size_t index) //???? ????????????????????????
    {
        if(nodeArray[index] == nullptr)
            return 0;
        
        int counter = 0;
        pNode tmp = nodeArray[index];
        while(tmp != nullptr)
        {
            tmp = tmp->next;
            ++counter;
        }
        return counter;
    }


    void am_arc_out(int from, int to) //?????????? ?????? ???? ???????? ??????????
    {

        int i = 1;
        if(from == to)
        {
            while (i < to)
            {
                cout << setw(STD_SETW) << '0';
                ++i;
            }
            cout << setw(STD_SETW) << (int)trash::IM_GRAPH::CYCLE; ++i;
            while (i <= nodeCount)
            {
                cout << setw(STD_SETW) << '0';
                ++i;
            }
            return;
        }else if(from > to)
        {
            while (i < to)
            {
                cout << setw(STD_SETW) << '0';
                ++i;
            }
                cout << setw(STD_SETW) << (int)trash::AM_GRAPH::TO; ++i;
            while (i < from)
            {
                cout << setw(STD_SETW) << '0';
                ++i;
            }
                cout << setw(STD_SETW) << (int)trash::AM_GRAPH::FROM; ++i;
            while (i <= nodeCount)
            {
                cout << setw(STD_SETW) << '0';
                ++i;
            }
        }
        else{
            while (i < from)
            {
                cout << setw(STD_SETW) << '0';
                ++i;
            }
                cout << setw(STD_SETW) << (int)trash::AM_GRAPH::FROM; ++i;
            while (i < to)
            {
                cout << setw(STD_SETW) << '0';
                ++i;
            }
                cout << setw(STD_SETW) << (int)trash::AM_GRAPH::TO; ++i;
            while (i <= nodeCount)
            {
                cout << setw(STD_SETW) << '0';
                ++i;
            }
        }
    }

    bool am_arc_to_il(string& sTmp)
    {
        int lastFrom = -1;  //???????????????????? ????????????????
        int lastTo = -1;    //???????????????????? ????????????????
        int iTmp = 0;
        int counter = 1;
        while(!sTmp.empty() && counter <= nodeCount) //????????????????.txt
        {
            iTmp = trash::str_to_int(sTmp);
                switch (iTmp)
                {
                case (int)trash::AM_GRAPH::VOID: break;

                case (int)trash::AM_GRAPH::CYCLE:{
                    add_last_node(counter - 1, counter);
                    return true;
                } break;

                case (int)trash::AM_GRAPH::FROM:{
                    if(lastFrom != -1)
                        return false;
                    else if(lastTo == -1)
                        lastFrom = counter;
                    else {
                        add_last_node(counter - 1, lastTo);
                        return true;
                    }
                     
                } break;

                case (int)trash::AM_GRAPH::TO:{
                    if(lastTo != -1)
                        return false;
                    else if(lastFrom == -1)
                        lastTo = counter;
                    else {
                        add_last_node(lastFrom - 1, counter);
                        return true;
                    }
                     
                } break;
                default: return false; break;
                }
                counter++;
        }
        return false;
    }


    bool im_line_to_il(string& sTmp, int index)
    {
        int iTmp = 0;
        int counter = 1;
        
        while (counter <= nodeCount && !sTmp.empty()) //????????????????.txt ??????: ????????
        {
            iTmp = trash::str_to_int(sTmp);
            switch (iTmp)
            {
            case (int)trash::IM_GRAPH::VOID: ++counter; continue; break;
            case (int)trash::IM_GRAPH::ARC:
            {
                if((index + 1) == counter)
                    return false;
                add_last_node(index, counter); 
            }break;
            case (int)trash::IM_GRAPH::CYCLE:
            {
                if((index + 1) != counter)
                    return false;
                add_last_node(index, counter); 
            }break;
            
            default: return false; break;
            }
        }
        return true;
    }   

    void head_text()
    {
        cout << endl << endl << setw(STD_SETW*2) << "colums: " << setw(STD_SETW - ((sizeof("colums: ") / sizeof(char)) - 1)) << '1';
        for(int i = 2; i <= nodeCount; i++)
            cout << setw(STD_SETW) << i;
        cout << endl << endl;
    }

protected:
    pNode *nodeArray;
    int nodeCount;
    
    void im_input()
    {
        cout << "\n\tInput ur graf like Identify Matrix: " << endl; //?????????????? ??????????????????
        head_text();

        string sTmp;
        for(int i = 0; i < nodeCount; i++)
        {
            do{
                delete nodeArray[i];
                nodeArray[i] = nullptr; 
                cout << setw(STD_SETW) << i+1 << ": ";
                getline(cin, sTmp);
            }while (!trash::is_int_unsigned(sTmp) || !im_line_to_il(sTmp, i));
            sort_and_del_reiteration_node(i);
        }

    }

    void il_input() //???????? ???????????? ??????????????????
    {
        //head_text();
        cout << "\n\tInput ur graf like Identify List: " << endl;
        string sTmp;
        for(int i = 0; i < nodeCount; i++)
        {
            do{
                cout << setw(STD_SETW) << i+1 << ": ";
                getline(cin, sTmp);
            }while (!trash::is_int_unsigned(sTmp));

            int iTmp = -1;
            while(!sTmp.empty())
            {
                iTmp = trash::str_to_int(sTmp);
                if(iTmp >= 1 && iTmp <= nodeCount)
                    add_last_node(i, iTmp);
            }
            sort_and_del_reiteration_node(i);
        }
    }

    void am_input()
    {
        int arcCount = cin_number(1, INT32_MAX, "Input count of arc in ur graph: ", "\nWrong arc count!\n");

        cout << "\n\tInput ur graf like Adjacency Matrix: " << endl; //?????????????? ??????????????????????????
        head_text();

        string sTmp;
        for(int i = 0; i < arcCount; i++)
        {
            do{
                cout << setw(STD_SETW) << i+1 << ": ";
                getline(cin, sTmp);
            }while (!trash::is_int(sTmp) || !am_arc_to_il(sTmp));

        }
        for(int i = 0; i < nodeCount; i++)
            sort_and_del_reiteration_node(i);
    }

public:

    IL_Graf()
    {
        nodeArray = NULL;
        nodeCount = 0;
    }

    IL_Graf(int nodeCount)
    {
        this->nodeCount = nodeCount;
        nodeArray = new pNode[nodeCount];
    }

    IL_Graf(IL_Graf& reference)
    {
        std::exception();
    }

    ~IL_Graf()
    {
        /*for(int i = 0; i < nodeCount; i++)
            nodeArray[i].del_all();*/
        delete[] nodeArray;
        
    }

    void safe_graph() //sale graph in file
    {
        std::ofstream MyFile("safe.txt");
        pNode nTmp;
        for(int i = 0; i < nodeCount; i++)
        {
            nTmp = nodeArray[i];
            while(nTmp)
            {
                MyFile << ' ' << nTmp->data;
                nTmp = nTmp->next;
            }
            MyFile << '\n';
        }
        MyFile.close();
    }

    void read_graph()
    {
        std::ifstream File("safe.txt");
        if(!File.is_open()) return;

        std::vector<string> fStrings;
        fStrings.push_back("");
        int i = 0;

        while(getline(File,fStrings[i++])) //???????????? ????????????????
        {
            cout << fStrings[i-1] << endl;
            if(fStrings[i-1].empty())
                fStrings[i-1].push_back('_');
            fStrings.push_back("");
        }fStrings.pop_back();

        if(i == 0) return;

        delete[]nodeArray;
        nodeCount = 0;
        
        nodeCount = fStrings.size();
        nodeArray = new pNode[nodeCount]{nullptr};
        
        int iTmp = -1;
        for(i = 0; i < nodeCount; i++)
        {

            while(!fStrings[i].empty())
            {
                iTmp = trash::str_to_int(fStrings[i]);
                if(iTmp >= 0 && iTmp <= nodeCount)
                    add_last_node(i, iTmp);
            }

            //sort_and_del_reiteration_node(i);
        }
        
        File.close(); 
    }


    void dfs()
    {
        if(nodeCount <= 0)
            return;
        bool* visited = new bool[nodeCount]{false};
        int* queue = new int[nodeCount]{0};
        queue[0] = 1;
        int i = 0, queueCounter = 1;
        bool anyConnect = false;
        pNode nTmp;
        while(queueCounter < nodeCount && i >= 0)
        {
            nTmp = nodeArray[queue[i]-1];
            anyConnect = false;
            while(nTmp)
            {
                if(!visited[nTmp->data])
                {
                    visited[nTmp->data] = true;
                    queue[queueCounter] = nTmp->data;
                    ++queueCounter;
                    anyConnect = true;
                    break;
                }
                nTmp = nTmp->next;
            }
            anyConnect?i = queueCounter-1:--i;
        }




        if(queueCounter == nodeCount)
        {
            cout << "\nDFS output: ";
            for(int i = 0; i < nodeCount; i++)
                cout << queue[i] << ' ';
        }
        else
        {
            cout << "\nNo way for DFS!!!"; 
            for(int i = 0; queue[i]; i++)
                cout << queue[i] << ' ';
        }
        cout << endl;
        delete[]visited;
        delete[]queue;
    }

    void bfs()
    {
        if(nodeCount <= 0)
            return;
        bool* visited = new bool[nodeCount]{false};
        int* queue = new int[nodeCount]{0};
        queue[0] = 1;
        int i = 0, queueCounter = 1;
        pNode nTmp;
        while(queueCounter < nodeCount && queue[i])
        {
            nTmp = nodeArray[queue[i++]-1];
            while(nTmp)
            {
                if(!visited[nTmp->data])
                {
                    visited[nTmp->data] = true;
                    queue[queueCounter] = nTmp->data;
                    ++queueCounter;
                }
                nTmp = nTmp->next;
            }
        }
        if(queueCounter == nodeCount)
        {
            cout << "\nBFS output: ";
            for(int i = 0; i < nodeCount; i++)
                cout << queue[i] << ' ';
        }
        else
            cout << "\nNo way for BFS!!!"; 
        cout << endl;
        delete[]visited;
        delete[]queue;
    }


    void input()
    {
        cout << "Choose one way to input ur graph" << endl;
        spam();
        int chosen = cin_number(1,3);

        
        nodeCount = cin_number(1, INT32_MAX, "Input count of node in ur graph: ", "\nWrong node count!\n");
        
        delete[] nodeArray;
        nodeArray = new pNode[nodeCount];
        for(int i = 0; i < nodeCount; i++)
            nodeArray[i] = nullptr;

        switch(chosen)
        {
            case (int)trash::TYPE_GRAPH::AM_GRAPH : am_input(); break;
            case (int)trash::TYPE_GRAPH::IM_GRAPH : im_input(); break;
            case (int)trash::TYPE_GRAPH::IL_GRAPH : il_input(); break;
            default: std::exception(); break;
        }
    }

    void output()
    {
        if(nodeCount == 0)
        {
            cout << "\nVoid graph!" << endl << endl;
            return;
        }

        cout << "Choose one way to output ur graph" << endl;
        spam();

        switch(cin_number(1,3))
        {
            case (int)trash::TYPE_GRAPH::AM_GRAPH : am_output(); break;
            case (int)trash::TYPE_GRAPH::IM_GRAPH : im_output(); break;
            case (int)trash::TYPE_GRAPH::IL_GRAPH : il_output(); break;
            default: std::exception(); break;
        }
    }

    void il_output()
    {
        head_text();
        for(int i = 0; i < nodeCount; i++)
        {
            cout << setw(STD_SETW) << i+1 << ": ";
            pNode nTmp = nodeArray[i];
            while (nTmp != nullptr)
            {
                cout << setw(STD_SETW) << nTmp->data;
                nTmp = nTmp->next;
            }
            cout << endl;
        }
    }

    void am_output()
    {
        // int arc_counter;
        // for(int i = 0; i < nodeCount; i++)
        //     arc_counter += node_count(i);
        head_text();
        int arc_counter = 1;

        for(int nCounter = 1; nCounter <= nodeCount; nCounter++)
        {
            pNode tmp = nodeArray[nCounter - 1];
            while(tmp != nullptr)
            {
                cout << setw(STD_SETW) << arc_counter << ':';
                am_arc_out(nCounter, tmp->data);
                cout << endl;

                tmp = tmp->next;
                ++arc_counter;
            }
        }
    }

    void im_output() //?????????? ???????? ??????????
    {
        head_text();
        for (int i = 0; i < nodeCount; i++)
        {
            cout << setw(STD_SETW) << i+1 << ':';
            for (int j = 0; j < nodeCount; j++)
            {
                if(find_in_node(i,j+1)) //???????? ?????????????????????? ???? ???????????? 3:11, ?? ???????????? ????????
                    if(i == j)
                        cout << setw(STD_SETW) << '2';
                    else
                        cout << setw(STD_SETW) << '1';
                else
                    cout << setw(STD_SETW) << '0';                        
            }
            cout << endl;
        }
        
    }
};

bool menu(IL_Graf& il_gr)
{
    cout << "\n\nChoose what u want to do with ur graph" << endl
    << "-1. Exit" << endl
    << "1. Input new graph" << endl
    << "2. Output ur graph" << endl
    << "3. BFS output" << endl
    << "4. DFS output" << endl
    << "5. Safe graph" << endl
    << "6. Get graph from file" << endl
    << "0. Repeat this message" << endl;

    switch(cin_number(-1, 7, "??hoose something from the menu: ", "Wrong choice!\n press '0' for help"))
    {
        case -1: return false; break;
        case 0: system("clear"); break;
        case 1: il_gr.input(); break;
        case 2: il_gr.output(); break;
        case 3: il_gr.bfs(); break;
        case 4: il_gr.dfs(); break;
        case 5: il_gr.safe_graph(); break;
        case 6: il_gr.read_graph(); break;
        default: std::exception(); break;
    }
    return true;
}

int main()
{
    IL_Graf a;
    
    // int f;
    // cin>>f;
    // a.bfs();
    // cin>>f;
    while (menu(a));
    
    return 0;
}