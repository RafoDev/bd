#include <bits/stdc++.h>
#include <direct.h>
#include <iostream>
#include <fstream>
#include <sstream>
#include <windows.h>
#include <limits>
#include <typeinfo> 
#include <chrono>
using namespace std::chrono;

using namespace std;

const string tablesDirectoryName = "Tablas";
const string metadata = "_metadata";
const string filesFormat = ".txt";
const char globalSplitter = ',';
string remove_spaces(string str)
{
    int tam = str.size();
    string tmp;
    for (int i = 0; i < tam; i++)
    {
        if (str[i] == ' ')
        {
            continue;
        }
        tmp += str[i];
    }
    return tmp;
}
vector<string> split_Character(string s, char c)
{
    vector<string> result;
    size_t pos = 0;
    std::string token;
    while ((pos = s.find(c)) != std::string::npos)
    {
        token = s.substr(0, pos);
        result.push_back(token);
        s.erase(0, pos + 1);
    }
    result.push_back(s);
    return result;
}
template< class T>
struct node
{
    T data;
    vector<int> pos;
    node<T> *ndes[2] = {};
    int weight=1;
	int height = 0;
    int space = 0;
    int st = 0;
    int fact=0;
    node(T d)
    {
        data = d;
    }
};
template<class T>
struct avl_tree
{
    node<T> *root=nullptr;
    void insert(T d, int index);
    bool find(T d, node<T> **&ptr, vector<node<T> **> &arr);
    void update(vector<node<T> **> &arr, int t);
    void inorder(node<T> *n);
    void balanceo(node<T> **n);
    bool search_nod(T d, node<T> *&pt);
	node<T>** rplce(vector<node<T> **> &arr, node<T> **m);
    void remove(T d);
};
template<class T>
void avl_tree<T>::balanceo(node<T> **n)
{
    if((*n)->fact==2)
    {
    	if(((*n)->ndes[1])->fact==1){
        	node<T> *nodeB=(*n)->ndes[1];
        	(*n)->ndes[1]=nodeB->ndes[0];
        	nodeB->ndes[0]=(*n);
        	(*n)=(nodeB);
			node<T> *l, *r, *p;
			p = (*n)->ndes[0]; l = p->ndes[0]; r = p->ndes[1];
			int x,y;
			x = l==nullptr?0:l->weight;
			y = r==nullptr?0:r->weight;
			p->weight = max(x,y)+1;
			(*n)->weight=max(((*n)->ndes[0])->weight, ((*n)->ndes[1])->weight)+1;
		}
		else
		{
            node<T> *a,*b,*c;
            a = (*n);
            b = ((*n)->ndes[1])->ndes[0];
            c = (*n)->ndes[1];
            T t;
            vector<int> pos_tmp;
            t = c->data;
            pos_tmp = c->pos;
            c->data = b->data; c->pos = b->pos; 
            b->data = t; b->pos=pos_tmp;
            a->ndes[1] = b->ndes[0];
            b->ndes[0] = b->ndes[1]; b->ndes[1] = c->ndes[1];
            c->ndes[0] = a; c->ndes[1] = b;
            (*n) = c;
            int x,y;
            x = a->ndes[0]==nullptr?0:(a->ndes[0])->weight;
            y = a->ndes[1]==nullptr?0:(a->ndes[1])->weight;
            a->weight = max(x,y)+1;
            x = b->ndes[0]==nullptr?0:(b->ndes[0])->weight;
            y = b->ndes[1]==nullptr?0:(b->ndes[1])->weight;
            b->weight = max(x,y)+1;
            c->weight = max(a->weight, b->weight)+1;
		}
    }
    else
	{
		if(((*n)->ndes[0])->fact==-1)
		{
        	node<T> *nodeB=(*n)->ndes[0];
			(*n)->ndes[0]=nodeB->ndes[1];
			nodeB->ndes[1]=(*n);
			(*n)=nodeB;
			node<T> *l, *r, *p;
			p = (*n)->ndes[1]; l = p->ndes[0]; r = p->ndes[1];
			int x,y;
			x = l==nullptr?0:l->weight;
			y = r==nullptr?0:r->weight;
			p->weight = max(x,y)+1;
			(*n)->weight=max(((*n)->ndes[0])->weight, ((*n)->ndes[1])->weight)+1;
		}
		else
		{
			node<T> *a,*b,*c;
			a = (*n);
			c = (*n)->ndes[0];
			b = ((*n)->ndes[0])->ndes[1];
			T t;
            vector<int> pos_tmp;
            t = c->data;
            pos_tmp = c->pos;
			c->data = b->data; c->pos = b->pos;
            b->pos = pos_tmp;
			b->data = t;
			a->ndes[0] = b->ndes[1];
			b->ndes[1] = b->ndes[0]; b->ndes[0] = c->ndes[0];
			c->ndes[0] = b; c->ndes[1] = a;
			(*n) = c;
			int x,y;
			x = b->ndes[0]==nullptr?0:(b->ndes[0])->weight;
			y = b->ndes[1]==nullptr?0:(b->ndes[1])->weight;
			b->weight = max(x,y)+1;
			x = a->ndes[0]==nullptr?0:(a->ndes[0])->weight;
			y = a->ndes[1]==nullptr?0:(a->ndes[1])->weight;
			a->weight = max(x,y)+1;
			c->weight = max(a->weight, b->weight)+1;
		}
	}
}
template<class T>
void avl_tree<T>::update(vector<node<T> **> &arr, int t)
{
    int len = arr.size();
	if(t){
		for(int i=len-1; i>=0; i--){
			int a,b;
			a = (*arr[i])->ndes[1]==nullptr?0:((*arr[i])->ndes[1])->weight;
			b = (*arr[i])->ndes[0]==nullptr?0:((*arr[i])->ndes[0])->weight;
			(*arr[i])->weight=(a!=b)?(*arr[i])->weight+1:(*arr[i])->weight;
			(*arr[i])->fact=a-b;
			if(a==b)
				return;
			if(abs((*arr[i])->fact)>1)
			{
				balanceo(arr[i]);
				return;
			}
		}
	}
	else
	{
		for(int i=len-1; i>=0; i--)
		{
			int x,y;
			x = (*arr[i])->ndes[0]==nullptr?0:((*arr[i])->ndes[0])->weight;
			y = (*arr[i])->ndes[1]==nullptr?0:((*arr[i])->ndes[1])->weight;
			(*arr[i])->weight = max(x,y)+1;
			(*arr[i])->fact = y-x;
			if(abs((*arr[i])->fact)>1)
				balanceo(arr[i]);
		}
	}
}
template<class T>
bool avl_tree<T>::find(T d, node<T> **&ptr, vector<node<T> **> &arr)
{
    for(ptr=&root; (*ptr)&&(*ptr)->data!=d;)
    {
        arr.push_back(ptr);
        ptr=&(*ptr)->ndes[((*ptr)->data)<(d)];
    }
    return ((*ptr)!=0);
}
template<class T>

bool avl_tree<T>::search_nod(T d, node<T> *&pt)
{
    for(pt=root; pt&&pt->data!=d;)
    {
        pt = pt->ndes[pt->data<d];
    }
    return pt!=0;
}

template<class T>
void avl_tree<T>::insert(T d, int index)
{
    vector<node<T> **> arr;
    node<T> **pt;
    if(find(d, pt, arr))
    {
        (*pt)->pos.push_back(index);
        return;
    }
    *pt=new node<T>(d);
    (*pt)->pos.push_back(index);
    update(arr,1);
}

template<class T>
node<T>** avl_tree<T>::rplce(vector<node<T> **> &arr, node<T> **m)
{
    node<T> **n;
	int i = 0;
	arr.push_back(m);
	n = &(*m)->ndes[i];
	for(; (*n)->ndes[!i]; n=&(*n)->ndes[!i])
		arr.push_back(n);
    return n;
}
template<class T>
void avl_tree<T>::remove(T d)
{
	node<T> **r;
	vector<node<T> **> arr;
	if(!find(d,r,arr))
		return;
	if((*r)->ndes[0]!=nullptr && (*r)->ndes[1]!=nullptr)
	{
		node<T> **q;
		q = rplce(arr,r);
		(*r)->data=(*q)->data;
		r=q;
	}
    node<T> *aux = *r;
	(*r)=(*r)->ndes[!(*r)->ndes[0]];
	update(arr, 0);
    delete aux;
}
template<class T>
void avl_tree<T>::inorder(node<T> *n)
{
    if(n==nullptr)
        return;
    inorder(n->ndes[0]);
    int len = n->pos.size();
    cout<<"key: \n"<<n->data<<endl;
    cout<<"Position(s): \n"<<endl;
    for(int i = 0; i < len; i++)
        cout<<n->pos[i]<<endl;
    inorder(n->ndes[1]);
}
node<string>* search_node(node<string> *r, string d)
{

    node<string> *g;
    for(g=r; g&&g->data!=d;)
    {

        if(g->data==d)
            return g;
        else{    

                stringstream tmp1(g->data);
                stringstream tmp2(d);
                int a,b;
                tmp1<<a;
                tmp2<<b;
                if(a>b)
                    g = g->ndes[0];
                else
                    g = g->ndes[1];
            // }
        }
    }
    return nullptr;
}
avl_tree<string> create_avl(vector<pair<string, int>> p)
{
    avl_tree<string> avl1;
    int len = p.size();
    for(int i = 0; i < len; i++)
    {   
        avl1.insert(p[i].first, p[i].second);
    }
    return avl1;
}

template<class T>
void get_datos(vector<string> data, vector<int> p,
avl_tree<T> &avl1, vector<string> tipos)
{
    ifstream fileTmp("Tablas/"+data[1]+"/"+data[1]+".txt");
    vector<string> n_colum;
    string n_columTmp;
    getline(fileTmp,n_columTmp,';');
    n_colum = split_Character(n_columTmp,',');
    fileTmp.close();
    ifstream file;
    file.open("Tablas/"+data[1]+"/"+data[1]+".txt");
    string output;
    while (getline(file, output))
        file >> output;
    //cout<<output<<endl;
    file.close();
    //{id,nombre,edad}
    //{10,10,2}
    string columna = data[2];
    int first = output.find(";");
    int len = output.size();
    string datos = output.substr(first+1, len-1);
    int pos = 0;
    for(int i=0; i<n_colum.size(); i++)
    {
        if(n_colum[i]==data[2]){
            pos = i;
            break;
        }
    }
    int peso = 0;
    for(int i = 0; i < pos; i++)
    {
        peso = peso + p[i];
    }
    peso = peso + pos;
    len = datos.size();
    int index = 0;
    int f = 0;
    int k = n_colum.size();
    vector<pair<string,int>> elements;
    while (f<len)
    {
        int l = p[index%k];
        if(index%k==pos)
        {
            pair<string, int> tmp;
            string ga = datos.substr(f,l);
            ga.erase(remove(ga.begin(), ga.end(), ' '), ga.end());
            tmp.first = ga;
            tmp.second = f-peso;
            elements.push_back(tmp);
        }
        f = f + p[index%k]+1;
        index++;
    }
    avl1 = create_avl(elements);

}
vector<string> getDataTypes(string tableName)
{
    ifstream file(string(tablesDirectoryName + "/" + tableName + "/" + tableName + metadata + filesFormat).c_str());
    string meta;
    getline(file, meta, ';');
    getline(file, meta, ';');
    vector<string> dataTypes, tmp;
    tmp = split_Character(meta, ',');
    for (auto i : tmp)
    {
        if (i.find("int") != std::string::npos)
        {
            dataTypes.push_back("int");
        }
        else if (i.find("char") != std::string::npos)
        {
            dataTypes.push_back("char");
        }
        else if (i.find("date") != std::string::npos)
        {
            dataTypes.push_back("date");
        }
    }
    return dataTypes;
}

void get_datos(string tabla,avl_tree<string> &avl)
{
    fstream file("Tablas/"+tabla+"/"+tabla+".txt");
    string reg;
    
    vector<pair<string,int>> elements;

    getline(file,reg,';');
    pair<string,int> tmp;

    int pfile = file.tellp();

    string key;


    while((pfile = file.tellp()) && getline(file,reg,';'))
    {
        key = remove_spaces(reg.substr(0,reg.find(",")));
        elements.push_back(pair<string,int>(key,pfile)); 
    }

    avl = create_avl(elements);
}




template<class T>
void UtilSerialize(node<T> *root, string index_name, string table_name, string &txt)
{
    if (root == nullptr)
    {
        txt = txt + "-1#";
        return;
    }
    txt = txt + (root->data)+",";
    int len = root->pos.size();
    int i = 0;
    for(; i<len-1; i++)
    {
        txt = txt + to_string(root->pos[i])+",";
    }
    txt = txt + to_string(root->pos[len-1])+"#";
    UtilSerialize(root->ndes[0], index_name, table_name, txt);
    UtilSerialize(root->ndes[1], index_name, table_name, txt);
}
template<class T>
void serialize(string index_name, string table_name, node<T> *root)
{
    ofstream file;
    string txt;
    file.open("Tablas/"+table_name+"/"+index_name+".txt");
    UtilSerialize(root, index_name, table_name, txt);
    file << txt;
    file.close();
}

template<class T>
void UtilDeSerialize(node<T> *&root, string &txt)
{
    string tmp;
    tmp  = txt.substr(0,txt.find("#"));
    txt = txt.substr(tmp.size()+1);
    vector<string> posi;
    posi = split_Character(tmp, ',');
   
    if(posi[0]=="-1")
        return;
    root = new node<T>(posi[0]);
    int len = posi.size();
    for(int i = 1; i < len; i++)
        root->pos.push_back(stoi(posi[i]));
    UtilDeSerialize(root->ndes[0], txt);
    UtilDeSerialize(root->ndes[1], txt);
}
template<class T>
avl_tree<string> Deserialize(node<T> *&root, string &txt)
{
    avl_tree<string> tree; 
    UtilDeSerialize(tree.root,txt);
    // tree.inorder(tree.root);
    return tree;
}

string remove_character(string str, char remChar)
{
    int tam = str.size();
    string tmp;
    for (int i = 0; i < tam; i++)
    {
        if (str[i] == remChar)
        {
            continue;
        }
        tmp += str[i];
    }
    return tmp;
}
string replace_character(string str, char oldchar, char newchar)
{
    for (auto &i : str)
        i = i == oldchar ? newchar : i;
    return str;
}

enum operations
{
    crear = 0,
    insertar = 1,
    seleccionar = 2,
    borrar = 3,
    modificar = 4,
    indice = 5
};

vector<string> processQuery(string query, int operation)
{
    query = remove_character(query, '\''); //borrar comillas
    string queryProcessed = query;

    //poner todo en minusculas
    for_each(queryProcessed.begin(), queryProcessed.end(), [](char &c)
             { c = ::tolower(c); });

    vector<string> result;

    vector<vector<string>> operationMatrix =
        {
            {"crear tabla", "(", ")"},
            {"insertar", "(", ")"},
            {"select * desde", "donde"},
            {"borrar desde", "donde"},
            {"modificar", "set", "=", "donde"},
            {"crea indice", "en", "."}};

    size_t found1, found2, found3, found4;

    //todos obtienen el nombre de la tabla de la misma manera
    found1 = queryProcessed.find(operationMatrix[operation][1]);
    int tmp = operationMatrix[operation][0].size();
    result.push_back(query.substr(tmp + 1, found1 - (tmp + 1) - 1)); //tableName
    //para crear e insertar
    if (operation == crear || operation == insertar)
    {
        query.pop_back();
        result.push_back(query.substr(found1 + 1)); //TableCols
    }
    //para seleccionar y borrar
    else if (operation == seleccionar || operation == borrar)
    {
        found2 = queryProcessed.find_first_of("=<>");
        int tmp1 = operationMatrix[operation][1].size();
        result.push_back(query.substr(found1 + tmp1 + 1, found2 - (found1 + tmp1 + 1) - 1)); //filtercol
        result.push_back(query.substr(found2, 1));                                           //condition
        result.push_back(query.substr(found2 + 2));                                          //filterData
    }
    //para modificar
    else if (operation == modificar)
    {
        found2 = queryProcessed.find("=");
        found3 = queryProcessed.find(operationMatrix[operation][3]);
        found4 = queryProcessed.find_last_of("=><");
        int tmp1 = operationMatrix[operation][1].size();
        int tmp2 = operationMatrix[operation][3].size();
        result.push_back(query.substr(found1 + tmp1 + 1, found2 - (found1 + tmp1 + 1) - 1)); //setcol
        result.push_back(query.substr(found2 + 2, found3 - (found2 + 2) - 1));               //setdata
        result.push_back(query.substr(found3 + tmp2 + 1, found4 - (found3 + tmp2 + 1) - 1)); //filter
        result.push_back(query.substr(found4, 1));
        result.push_back(query.substr(found4 + 2));
    }
    // CREA_INDICE IDX_80000 EN “tb_estudiante”.”id_est”
    else if (operation == indice)
    {
        found2 = queryProcessed.find(operationMatrix[operation][2]);
        int tmp1 = operationMatrix[operation][1].size();
        result.push_back(query.substr(found1 + tmp1 + 1, found2 - (found1 + tmp1 + 1)));
        result.push_back(query.substr(found2 + 1));
    }

    return result;
}


vector<int> getNeededSpace(vector<string> fields)
{
    vector<int> result;
    for (auto i : fields)
    {
        if (i.find("int") != std::string::npos || i.find("char") != std::string::npos)
        {
            result.push_back(stoi(i.substr(i.find("(") + 1, i.find(")") - 1)));
        }
        else if (i.find("date") != std::string::npos)
        {
            result.push_back(10);
        }
    }
    return result;
}

void createOP(string query)
{
    vector<string> fields = processQuery(query, 0);
    mkdir(tablesDirectoryName.c_str());
    mkdir(string(tablesDirectoryName + "/" + fields[0]).c_str());

    fstream file;
    file.open(string(tablesDirectoryName + "/" + fields[0] + "/" + fields[0] + filesFormat).c_str(), std::fstream::out);

    // "Crear Tabla Estudiante (ID_est-int(12), nom-char(30), ape-char(30), edad-int(12), fecnac-date)"
    vector<string> colNames = split_Character(fields[1], ',');
    string tmp_names;
    for (auto i : colNames)
    {
        i = i.substr(0, i.find("-"));
        tmp_names += remove_spaces(i) + ',';
    }
    tmp_names.pop_back();
    tmp_names += ';';
    file << tmp_names;

    file.close();
    file.open(string(tablesDirectoryName + "/" + fields[0] + "/" + fields[0] + metadata + filesFormat).c_str(), std::fstream::out);
    file << fields[0] << ';';
    file << remove_spaces(fields[1]) << ';';

    vector<int> tmp = getNeededSpace(split_Character(fields[1], ','));
    int sum = 0;
    string tmp_cols;
    for (auto i : tmp)
    {
        sum += i;
        tmp_cols += to_string(i) + ',';
    }
    tmp_cols.pop_back();
    tmp_cols += ';';
    file << tmp_cols;
    file.close();

    tmp_names.pop_back();
    tmp_cols.pop_back();

    cout << "Tabla creada : " << fields[0] << endl;
    cout << "Columnas(" << colNames.size() << ") : " << tmp_names << endl;
    cout << "Bytes : " << tmp_cols << endl;
}

//Obtiene cuantos bytes debe ocupor cada columna
vector<int> getSpacePerCol(string tableName)
{
    fstream file;
    file.open(string(tablesDirectoryName + "/" + tableName + "/" + tableName + metadata + filesFormat).c_str(), std::fstream::in);

    string line;
    string file_contents;
    while (std::getline(file, line))
    {
        file_contents += line;
    }
    vector<string> tmp_string = split_Character(file_contents, ';');
    tmp_string = split_Character(tmp_string[2], ',');
    vector<int> tmp_int;
    for (auto i : tmp_string)
    {
        tmp_int.push_back(stoi(i));
    }
    return tmp_int;
}
bool indexInTable(string tableName)
{
    ifstream file("Tablas/"+tableName+"/"+tableName+"_metadata.txt");
    int i = 0;
    string tmp;
    while(getline(file,tmp,';'))
    {
        i++;
    }
    return i>3;
}
bool indexInTable(string tableName,string &indexName)
{
    ifstream file("Tablas/"+tableName+"/"+tableName+"_metadata.txt");
    int i = 0;
    string tmp;
    while(getline(file,tmp,';'))
    {
        indexName = tmp;
        i++;
    }
    return i>3;
}
void insertOP(string query)
{
    //obtenemos el nombre del la tabla y las columnas
    vector<string> fields = processQuery(query, 1);
    fields[1] = remove_spaces(fields[1]);
    //abrimos el archivo
    fstream file;
    file.open(string(tablesDirectoryName + "/" + fields[0] + "/" + fields[0] + filesFormat).c_str(), fstream::app);

    //vector con los espacios disponibles
    vector<int> colsSpaces = getSpacePerCol(fields[0]);
    //vector con los datos
    vector<string> colsData = split_Character(fields[1], ',');

    colsData.pop_back();

    string registerTmp;

    //calculamos cuanto espacio extra hay y lo agregamos por cada col
    size_t tam = colsData.size();
    for (size_t i = 0; i < tam + 1; i++)
    {
        int tmp = colsSpaces[i] - colsData[i].size();
        registerTmp += colsData[i];
        for (int j = 0; j < tmp; j++)
        {
            registerTmp += " ";
        }
        registerTmp += ",";
    }
    registerTmp.pop_back();
    registerTmp.push_back(';');

    file << registerTmp;
    file.close();
    string indexName;
    if(indexInTable(fields[0],indexName))
    {
        vector<int> colSpaces = getSpacePerCol(fields[0]);
        vector<string> colTypes = getDataTypes(fields[0]);
        avl_tree<string> avl1;
        get_datos(fields[0],avl1);
        // get_datos(fields,colSpaces,avl1,colTypes);
        serialize(indexName,fields[0],avl1.root);
    }
}

bool operationsCondition(string a, string b, string condition)
{
    bool result = 0;
    if (condition == "=")
    {
        result = a == b;
    }
    else if (condition == "<")
    {
        result = stoi(a) < stoi(b);
    }
    else if (condition == ">")
    {
        result = stoi(a) > stoi(b);
    }
    return result;
}

void selectOP(string query)
{   
    auto start = high_resolution_clock::now();
    vector<string> fields = processQuery(query, 2);

    cout<<"Seleccion sin indice"<<endl;
    ifstream file;
    file.open(string(tablesDirectoryName + "/" + fields[0] + "/" + fields[0] + filesFormat).c_str());
    string tablefields;
    getline(file, tablefields, ';');

    cout << tablefields << endl;
    int tamFields = tablefields.size();
    for(int i = 0;i<tamFields;i++)
    {
        cout<<"-";
    }
    cout<<endl;

    int tmp = tablefields.find(fields[1]);
    int nField = 0;
    for (int i = 0; i < tmp; i++)
    {
        if (tablefields[i] == ',')
            nField++;
    }
    string line;
    int returnedLines = 0;
    //lee linea por linea, delimitando por ; de modo que line obtiene un registro tratable
    while (getline(file, line, ';'))
    {   
        string tmpline = remove_spaces(line);
        vector<string> registerTmp = split_Character(tmpline, ',');

        if (operationsCondition(registerTmp[nField], fields[3], fields[2]))
        {
            cout << line << endl;
            returnedLines++;
        }
    }
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Todo ha salido bien, registros devueltos: " << returnedLines <<", " <<duration.count()<< " milisegundos." << endl;
}
void deleteOP(string query)
{
    vector<string> fields = processQuery(query, 3);
    for (auto i : fields)
    {
        cout << i << " ";
    }
    cout << endl;
    ifstream file;

    file.open(string(tablesDirectoryName + "/" + fields[0] + "/" + fields[0] + filesFormat).c_str());
    string tablefields;
    getline(file, tablefields, ';');

    int tmp = tablefields.find(fields[1]);
    int nField = 0;
    for (int i = 0; i < tmp; i++)
    {
        if (tablefields[i] == ',')
            nField++;
    }
    string line;
    ofstream file_tmp;
    file_tmp.open(string(tablesDirectoryName + "/" + fields[0] + "/" + "tmp" + filesFormat).c_str());
    file_tmp << tablefields << ";";

    int deletedLines = 0;
    //lee linea por linea, delimitando por ; de modo que line obtiene un registro tratable
    while (getline(file, line, ';'))
    {
        vector<string> registerTmp = split_Character(line, ',');

        if (!operationsCondition(remove_spaces(registerTmp[nField]), fields[3], fields[2]))
        {
            file_tmp << line << ";";
        }
        else
        {
            deletedLines++;
        }
    }
    file.close();
    file_tmp.close();
    remove(string(tablesDirectoryName + "/" + fields[0] + "/" + fields[0] + filesFormat).c_str());
    rename(string(tablesDirectoryName + "/" + fields[0] + "/" + "tmp" + filesFormat).c_str(), string(tablesDirectoryName + "/" + fields[0] + "/" + fields[0] + filesFormat).c_str());
    string indexName;
    if(indexInTable(fields[0],indexName))
    {
        vector<int> colSpaces = getSpacePerCol(fields[0]);
        vector<string> colTypes = getDataTypes(fields[0]);
        avl_tree<string> avl1;
        // get_datos(fields,colSpaces,avl1,colTypes);

        get_datos(fields[0],avl1);
        serialize(indexName,fields[0],avl1.root);
        cout<<endl<<"Arbol Actualizado"<<endl;
        cout << "Registros borrados : " << deletedLines << endl;
    }
    else{
        cout << "Registros borrados : " << deletedLines << endl;
    }
}
// string query5 = "MODIFICAR Estudiante(0) SET nom(1) = 'Rensso'(2) DONDE id_est(3) <(4) 1(5)";
// ID_est-int(12), nom-char(30), ape-char(30), edad-int(12), fecnac-date
void updateOP(string query)
{
    vector<string> fields = processQuery(query, 4);
    ifstream file;

    file.open(string(tablesDirectoryName + "/" + fields[0] + "/" + fields[0] + filesFormat).c_str());
    string tablefields;
    getline(file, tablefields, ';');

    int tmp = tablefields.find(fields[1]);
    int tmp1 = tablefields.find(fields[3]);

    int nFieldSet = 0, nFieldFilter = 0;
    for (int i = 0; i < tmp; i++)
    {
        if (tablefields[i] == ',')
            nFieldSet++;
    }
    for (int i = 0; i < tmp1; i++)
    {
        if (tablefields[i] == ',')
            nFieldFilter++;
    }

    string line;
    ofstream file_tmp;
    file_tmp.open(string(tablesDirectoryName + "/" + fields[0] + "/" + "tmp" + filesFormat).c_str());
    file_tmp << tablefields << ";";

    int uploadedLines = 0;
    //lee linea por linea, delimitando por ; de modo que line obtiene un registro tratable
    while (getline(file, line, ';'))
    {
        vector<string> registerTmp = split_Character(line, ',');

        if (operationsCondition(remove_spaces(registerTmp[nFieldFilter]), fields[5], fields[4]))
        {
            if (remove_spaces(registerTmp[nFieldSet]) != fields[2]) //Si ambos son iguales entonces no habra ningun cambio
            {
                uploadedLines++;
                string regtotxt;
                string setData = fields[2];

                // Agregamos espacios para mantener la consistencia
                for (int i = 0; i < registerTmp[nFieldSet].size() - fields[2].size(); i++)
                {
                    setData.push_back(' ');
                }
                registerTmp[nFieldSet] = setData;
                // Unificamos el vector de strings para que entre al txt
                for (auto i : registerTmp)
                {
                    regtotxt += i + ',';
                }
                regtotxt.pop_back();
                regtotxt += ";";
                file_tmp << regtotxt;
            }
            else
            {
                file_tmp << line << ";";
            }
        }
        else
        {
            file_tmp << line << ";";
        }
    }
    cout << "Registros actualizados :" << uploadedLines << endl;
    file.close();
    file_tmp.close();
    remove(string(tablesDirectoryName + "/" + fields[0] + "/" + fields[0] + filesFormat).c_str());
    rename(string(tablesDirectoryName + "/" + fields[0] + "/" + "tmp" + filesFormat).c_str(), string(tablesDirectoryName + "/" + fields[0] + "/" + fields[0] + filesFormat).c_str());
}




void indexOP(string query)
{
    // fields[0] = nombre del indice, fields[1] = nombre de la tabla, fields[2] = nombre de la columna
    vector<string> fields = processQuery(query, 5);

    avl_tree<string> avl1;

    get_datos(fields[1],avl1);
    serialize(fields[0],fields[1],avl1.root);

    fstream file("Tablas/"+fields[1]+"/"+fields[1]+"_metadata.txt",std::fstream::app);
    file<<fields[0]<<";";
}


string fechaRandom()
{
    string fcha;
    int dia = rand() % 31 + 1;
    fcha += to_string(dia) + "-";
    int mes = rand() % 12 + 1;
    fcha += to_string(mes) + "-";
    int anho = rand() % 11 + 1970;
    fcha += to_string(anho);
    return fcha;
}
string cadenaRandom(int tam, string abc)
{
    string cadena;
    int abcTam = abc.size() - 1;
    tam = rand() % tam + 1;
    while (tam)
    {
        cadena += abc[rand() % abcTam + 1];
        if (abcTam < rand() % abcTam + 1)
        {
            cout << "ERRORRR";
        }
        tam--;
    }
    return cadena;
}


void writeFromFile(string tableName, vector<int> positions)
{
    fstream table;
    table.open("Tablas/"+tableName+"/"+tableName+".txt",fstream::in);
    string tmp;
    getline(table,tmp,';');
    cout<<tmp<<endl;
    int tamColsName = tmp.size();
    for(int i = 0;i<tamColsName;i++)
    {
        cout<<"-";
    }
    cout<<endl;
    int tam = positions.size();
    for(int i= 0;i<tam;i++)
    {
        string reg;
        table.seekp(positions[i]);
        getline(table,reg,';');
        cout<<reg<<endl;
    }
    cout<<'\n';
}

//select desde estudiante donde id=1;
void select_index(string query)
{
    auto start = high_resolution_clock::now();
    
    avl_tree<string> avl1;
    node<int> *tmp1;
    node<string> *tmp2;

    vector<string> process = processQuery(query,2);
    vector<string> col_types = getDataTypes(process[0]);
    vector<int> p = getSpacePerCol(process[0]);

    fstream file;
    file.open("Tablas/"+process[0]+"/"+process[0]+".txt", fstream::in);
    string tmp;
    getline(file, tmp, ';');
    file.close();
    vector<string> col_names = split_Character(tmp,',');
    int i = 0;
    for(; i < col_names.size(); i++)
    {
        if(col_names[i]==process[1])
            break;
    }

    //hola   ,jose   ,17
    string tipo_dato = col_types[i];
    string txt;
    fstream file2;

    file2.open("Tablas/"+process[0]+"/"+process[0]+"_metadata.txt", fstream::in);
    string tmp3;
    getline(file2, tmp3);

    string idx = split_Character(tmp3,';')[3];
    file2.close();

    file2.open("Tablas/"+process[0]+"/"+idx+".txt", fstream::in);
    getline(file2, txt);

    avl1=Deserialize(avl1.root, txt);
    //avl1.inorder(avl1.root);

    file2.close();

    node<string> *c;
    avl1.search_nod(process[3], c);


    int nPositions = c->pos.size();
    cout<<"Seleccion con indice"<<"\n\n";

    //write from file 
    fstream table;
    table.open("Tablas/"+process[0]+"/"+process[0]+".txt",fstream::in);
    string tmp4;
    getline(table,tmp4,';');
    cout<<tmp4<<endl;

    int tamColsName = tmp4.size();
    for(int i = 0;i<tamColsName;i++)
    {
        cout<<"-";
    }
    cout<<endl;
    int tam = c->pos.size();
    for(int i= 0;i<tam;i++)
    {
        string reg;
        table.seekp(c->pos[i]);
        getline(table,reg,';');
        cout<<reg<<endl;
    }
    cout<<'\n';
    
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);

    cout << "Todo ha salido bien, registros devueltos: " << nPositions <<", " <<duration.count()<< " milisegundos." << endl;
}


// Sistema Gestor de Bases de Datos (SGBD)
void sgbd()
{
    // system("Color DE");
    system("cls");
    for (int i = 0; i < 120; i++)
        cout << "-";
    cout << "\n";
    cout << "SGBD: Donut v0.1"  << endl;
    cout << "\n";
    string query;
    while (query.compare("exit") != 0)
    {

        fstream file(string("historial.txt").c_str(), std::fstream::app);
        auto t = std::time(nullptr);
        auto tm = *std::localtime(&t);

        cout << "> " << put_time(&tm, "%H:%M") << " ";
        getline(cin, query);
        file << put_time(&tm, "%H:%M");
        file << " ";
        file << query;
        file << "\n";
        file.close();

        cout << "\n";
        string queryPreProcessed = query;

        for_each(queryPreProcessed.begin(), queryPreProcessed.end(), [](char &c)
                 { c = ::tolower(c); });
        if (query.compare("exit") != 0)
        {
            if (queryPreProcessed.find("donut --version") != std::string::npos)
            {
                    cout << "SGBD: Donut v0.1" << endl;
                    cout << "Intregrantes:"<<endl;
                    cout<< "    Brian, Elias, Rafael"<<endl;
            }
            else if (queryPreProcessed.find("crear tabla") != std::string::npos)
            {
                createOP(query);
            }
            else if (queryPreProcessed.find("insertar") != std::string::npos)
            {
                insertOP(query);
            }
            else if (queryPreProcessed.find("borrar") != std::string::npos)
            {
                deleteOP(query);
            }
            else if (queryPreProcessed.find("select") != std::string::npos)
            {
                vector<string> tmp = processQuery(query,2);
                if(indexInTable(tmp[0]))
                {
                    select_index(query);
                }
                else{
                    selectOP(query);
                }
            }
            else if (queryPreProcessed.find("modificar") != std::string::npos)
            {
                updateOP(query);
            }
            else if (queryPreProcessed.find("crea indice") != std::string::npos)
            {
                indexOP(query);
            }
            else if (queryPreProcessed.find("restart")!=std::string::npos)
            {
                system(".\\run.bat");
            }
            else if (query.substr(0, 6).compare("random") == 0)
            {
                if (query.size() > 7)
                {
                    vector<string> tmp = split_Character(query, ' ');
                    vector<int> colsSpaces = getSpacePerCol(tmp[1]);
                    vector<string> colsTypes = getDataTypes(tmp[1]);
                    int nRegs = stoi(tmp[2]);
                    int nCols = colsSpaces.size();
                    string insertion;
                    for (int i = 0; i < nRegs; i++)
                    {
                        insertion = "insertar " + tmp[1] + " (";
                        for (int j = 0; j < nCols; j++)
                        {
                            if (colsTypes[j] == "int")
                            {
                                insertion += cadenaRandom(colsSpaces[j], "123456789");
                            }
                            else if (colsTypes[j] == "char")
                            {
                                insertion += cadenaRandom(colsSpaces[j], "abcdefghijklmnopqrstuvwxyz");
                            }
                            else
                            {
                                insertion += fechaRandom();
                            }
                            insertion += ",";
                        }
                        insertion.pop_back();
                        insertion += ")";
                        insertOP(insertion);
                    }
                }
                else
                {
                    cout << "Comando incorrecto, intente nuevamente" << endl;
                }
            }
            else if (query.substr(0, 5).compare("start") == 0)
            {
                if (query.size() > 6)
                {
                    string tabla = query.substr(6);
                    system(string("start Tablas\\" + tabla + "\\" + tabla + ".txt").c_str());
                }
                else
                {
                    cout << "Comando incorrecto, intente nuevamente" << endl;
                }
            }
            else if (query.substr(0, 4).compare("copy") == 0)
            {
                if (query.size() > 5)
                {
                    string tabla1 = query.substr(5, query.find_last_of(" ") - 5);
                    string tabla2 = query.substr(query.find_last_of(" ") + 1);
                    system(string("mkdir Tablas\\" + tabla2 + ">nul").c_str());
                    system(string("xcopy Tablas\\" + tabla1 + " Tablas\\" + tabla2 + ">nul").c_str());

                    ifstream fileIn(string("Tablas/" + tabla2 + "/" + tabla1 + metadata + filesFormat).c_str());
                    ofstream fileOut(string("Tablas/" + tabla2 + "/" + tabla2 + metadata + filesFormat).c_str());

                    string line;
                    string tmp;
                    getline(fileIn, line, ';');
                    fileOut << tabla2;
                    fileOut << ";";

                    while (getline(fileIn, line, ';'))
                    {
                        fileOut << line << ";";
                    }

                    fileIn.close();
                    fileOut.close();

                    rename(string("Tablas/" + tabla2 + "/" + tabla1 + ".txt").c_str(), string("Tablas/" + tabla2 + "/" + tabla2 + ".txt").c_str());
                    remove(string("Tablas/" + tabla2 + "/" + tabla1 + metadata + filesFormat).c_str());
                    cout << tabla1 << " fue replicada en " << tabla2 << endl;
                }
                else
                {
                    cout << "Comando incorrecto, intente nuevamente" << endl;
                }
            }
            else if (query.substr(0, 5).compare("field") == 0)
            {
                if (query.size() > 7)
                {
                    vector<string> tmp = split_Character(query, ' ');
                    vector<int> colsSpaces = getSpacePerCol(tmp[1]);
                    vector<string> colsTypes = getDataTypes(tmp[1]);
                    int nRegs = stoi(tmp[2]);
                    int nCols = colsSpaces.size();
                    string insertion;
                    for (int i = 0; i < nRegs; i++)
                    {
                        insertion = "insertar " + tmp[1] + " (";
                        for (int j = 0; j < nCols; j++)
                        {
                            if (colsTypes[j] == "int")
                            {
                                //insertion += cadenaRandom(colsSpaces[j], "123456789");
                                insertion = insertion + to_string(i);
                            }
                            else if (colsTypes[j] == "char")
                            {
                                //insertion += cadenaRandom(colsSpaces[j], "abcdefghijklmnopqrstuvwxyz");
                                insertion = insertion + "nombre" + to_string(i);
                            }
                            else
                            {
                                insertion += fechaRandom();
                            }
                            insertion += ",";
                        }
                        insertion.pop_back();
                        insertion += ")";
                        insertOP(insertion);
                    }
                }
                
                else
                {
                    cout << "Comando incorrecto, intente nuevamente" << endl;
                }
            }
            else if (query.substr(0, 2).compare("ls") == 0)
            {
                ofstream file;
                file.open("mt.ps1");

                string powershell;
                powershell = "Get-ChildItem -Path Tablas -name  -exclude metadata";
                file << powershell << endl;
                file.close();

                system("powershell -ExecutionPolicy Bypass -F mt.ps1");

                remove("mt.ps1");
            }
            else if (query.compare("help") == 0)
            {
                cout << "uso: donut [--version]\n"
                     << endl;
                cout << "Plantillas de consultas existentes: " << endl;
                cout << "     CREAR TABLA nombre_tabla (campo1-int(12),campo2-char(20))" << endl;
                cout << "     INSERTAR nombre_tabla (dato1,dato2)" << endl;
                cout << "     SELECT * DESDE nombre_tabla DONDE campo1 = dato1" << endl;
                cout << "     BORRAR DESDE nombre_tabla DONDE campo1 = dato1" << endl;
                cout << "     MODIFICAR nombre_tabla SET campo1 = dato1 DONDE campo2 = dato2"<<endl;
                cout << "     CREA INDICE idx EN nombre_tabla.campo1"<<"\n"<< endl;

                cout << "Comandos Donut utiles en varias situaciones:" << endl;
                cout << "     ls                              Muestra las tablas" << endl;
                cout << "     start <tabla>                   Abre el archivo txt de la tabla deseada" << endl;
                cout << "     copy  <tabla1> <tabla2>         Copia el contenido de una tabla a otra" << endl;
                cout << "     random <tabla> <nroRegistros>   Llena la tabla de datos random" << endl;
                cout << "     field                           Llena la tabla de datos ordenados" << endl;
                cout << "     exit                            Salir del programa\n"
                     << endl;
            }
            else if (query.empty())
            {
                continue;
            }
            else
            {
                cout << query << " : No existe, intente nuevamente" << endl;
            }
            cout << "\n";
        }
    }
}



int main()
{
    sgbd();
    // avl_tree<string> a;
    // get_datos("tb",a);
    
    //string query = "CREA INDICE idx EN estudiante.id";
    // indexOP(query);
    // avl_tree<string> avl;

    // get_datos("estudiante",avl);

    // avl.inorder(avl.root);  
        // avl_tree<int> tree;
    // string ga ="943,58#56,0#5,232#-1#-1#-1#4444,116#3378,174#-1#-1#-1#";
    // Deserialize(tree.root,ga);
    //select_index("select * desde estudiante donde id = 2");
    // string x = "abcde";
    // if(x.find_first_of("fgh")!=std::string::npos)
    //     cout<<"sdsd"<<endl;
}