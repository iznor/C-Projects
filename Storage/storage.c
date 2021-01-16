// Storage
                      
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct st_items{
    int num;
    char name[20];
    
} items;

typedef struct st_cells{
    int num;
    items item;
} cells;

typedef struct st_shelves{
    int num;
    cells *cell;
} shelves;

int glob_shelves = 0;
int glob_cells = 0;
int glob_total_items = 0;
int last_item_num = 0;
shelves *shelf;

//ERRORS
void myERROR(void);
void addERROR(void);
void swapERROR(void);
void moveERROR(void);
void printERROR(void);
void removeERROR(void);
void action_valid(char action[]);
//Technical Functions
int Arg_Check(int argc, int n);                              //prints "error" if argc < n
int fp_Check(FILE *fp);                                      //prints "error" if fp==NULL
void free_a(void);                                           //implements "free" function on all allocated mem.
//Help Functions
void shelves_quant(int shelves_num);                         //decides how many shelves in storage
void cells_quant(int cells_num);                             //decides how many cells in storage
int foundShelf(int shelf_num);                               // returns 0 or 1
int foundCell(int cell_num);                                 // returns 0 or 1
int Freecells_from(int shelf_num, int from_cell, int quant); // returns 0 or 1
int Freecells_inShelf(int shelf_num, int quant);             // returns -1 or cell index
int Freecells_Anywhr2(int quant, int curr_shelf);            // if enough free cells FROM THE NEXT shelf -returns shelf num
int Freecells_Anywhr(int quant);                             // if enough free cells ANYWHERE in storage -returns shelf num
void add_somewhere2(char *item_name, int quant, int curr_shelf); // tries to add items AFTER current shelf
void add_somewhere(char *item_name, int quant);              // add items ANYWHERE in storage
void input_items(char item_name[], int shelf_num, int cell_num, int quant); //inputs item/s to specific location
void New_Shelf(void);                                        // add new shelf to storage
void Clear_Cell(int shelf_num, int cell_num);                // delete content of a specific cells
void Swap(int shelfA, int cellA, int shelfB, int cellB);     // swaps between two specific location
int shelf_of_an_item(int item_num);                          // returns the shelf of item number n
int cell_of_an_item(int item_num);                           // returns the cell of item number n
int shelf_empty(int shelf_num);                              // returns 1 if a specific shelf is empty
int last_shelf_is_empty(void);                               // returns 1 if a the last shelf is empty
void Remove_last_Shelf(void);                                // removes last shelf
void compress_shelves(void);                                 // minimize spaces between items
void compress_cells(void);                                   // shelf[x]'s first item goes to shelf[x-1]'s last cell
void move_item2(int shelfA, int cellA, int shelfB, int cellB); // variation 2 of original move func

//Main Functions
void add_item(char *item_name, int shelf_num, int cell_num, int quant);
void remove_item(int shelf_num, int cell_num);
void move_item(int shelfA, int cellA, int shelfB, int cellB);
void switch_items(int shelfA, int cellA, int shelfB, int cellB);
void print_item(int item_number);
void print_storage(void);
void matrix(void);
void minimize_storage(void);

//MAIN
int main(int argc, char const *argv[]){
    char buf[100] = {0};
    char curr_func[10] = {0};
    int i = 0;
    FILE *fp;
        fp = fopen("storage.txt", "r");
        if (fp_Check(fp))
            while (fgets(buf, 100, fp) != NULL){
                fscanf(fp, "%s", curr_func);
                if (curr_func[0] != '#'){
                    action_valid(curr_func);
                    if (strcmp(curr_func, "_isc") == 0){
                        fscanf(fp, "%d", &glob_shelves);
                        shelves_quant(glob_shelves);
                    }
                    if (strcmp(curr_func, "_msps") == 0){
                        fscanf(fp, "%d", &glob_cells);
                        cells_quant(glob_cells);
                    }
                    if (strcmp(curr_func, "_add") == 0){
                        char itemName[30] = {0};
                        int quantity, to_shelf, to_cell;
                        fscanf(fp, "%s", itemName);
                        fscanf(fp, "%d", &quantity);
                        fscanf(fp, "%d", &to_shelf);
                        fscanf(fp, "%d", &to_cell);
                        add_item(itemName, to_shelf, to_cell, quantity);
                        ++last_item_num;
                    }
                    if (strcmp(curr_func, "_rm") == 0){
                        int ShelfToRemove, CellToRemove;
                        fscanf(fp, "%d", &ShelfToRemove);
                        fscanf(fp, "%d", &CellToRemove);
                        remove_item(ShelfToRemove, CellToRemove);
                    }
                    if (strcmp(curr_func, "_mv") == 0){
                        int shelfA, cellA, shelfB, cellB;
                        fscanf(fp, "%d", &shelfA);
                        fscanf(fp, "%d", &cellA);
                        fscanf(fp, "%d", &shelfB);
                        fscanf(fp, "%d", &cellB);
                        move_item(shelfA, cellA, shelfB, cellB);
                    }
                    if (strcmp(curr_func, "_sw") == 0){
                        int shelf1, cell1, shelf2, cell2;
                        fscanf(fp, "%d", &shelf1);
                        fscanf(fp, "%d", &cell1);
                        fscanf(fp, "%d", &shelf2);
                        fscanf(fp, "%d", &cell2);
                        switch_items(shelf1, cell1, shelf2, cell2);
                    }
                    if (strcmp(curr_func, "_pi") == 0){
                        int item_num_to_print;
                        fscanf(fp, "%d", &item_num_to_print);
                        print_item(item_num_to_print);
                    }
                    if (strcmp(curr_func, "_ps") == 0){
                        print_storage();
                        printf("\n");
                    }
                    if (strcmp(curr_func, "_min") == 0){
                        minimize_storage();
                    }                    
                    if (strcmp(curr_func, "_mtrx") == 0){
                        matrix();
                        printf("\n");
                        break;
                    }
                }   
            }
    free_a();
    fclose(fp);

    return 0;
}
//ERRORS
void myERROR(void)
{
    fprintf(stderr, "%s", "Error- action does not exist!\n");
    return;
}
void addERROR(void)
{
    fprintf(stderr, "%s", "ADD- one/two of the parameters are illegal!\n");
    return;
}
void swapERROR(void)
{
    fprintf(stderr, "%s", "SWAP- one/two of the locations are not legal!\n");
    return;
}
void moveERROR(void)
{
    fprintf(stderr, "%s", "MOVE- one/two of the locations are not legal!\n");
    return;
}
void printERROR(void)
{
    fprintf(stderr, "%s", "PRINT ITEM- the item number is not legal!\n");
    return;
}
void removeERROR(void)
{
    fprintf(stderr, "%s", "REMOVE- the item location is not legal\n");
    return;
}
void action_valid(char action[])
{
    if (strcmp(action, "_isc")==0 || strcmp(action, "_msps")==0 || strcmp(action, "_add")==0||
         strcmp(action, "_rm")==0 || strcmp(action, "_mv")==0 || strcmp(action, "_sw")==0||
         strcmp(action, "_pi")==0 || strcmp(action, "_ps")==0 || strcmp(action, "_mtrx")==0|| 
         strcmp(action, "_min")==0){
            return;
        }
    myERROR();
    return;
}
//technical
int Arg_Check(int argc, int n) 
{
    if (argc < n)
    {
        myERROR();
        return 0;
    }
    return 1;
}
int fp_Check(FILE *fp)
{
    if (fp == NULL)
    {
        myERROR();
        return 0;
    }
    return 1;
}
void free_a(void)
{
    for (int i = 0; i < glob_shelves; i++){
        free(shelf[i].cell);
    }
    free(shelf);
}
//Help Functions
void shelves_quant(int shelves_num)
{
    glob_shelves = shelves_num;
    return;
}
void cells_quant(int cells_num)
{
    int i;
    glob_cells = cells_num;
    shelves *shelf_p = (shelves *)malloc(glob_shelves * sizeof(shelves));
    if (shelf_p==NULL)
    {
        myERROR();
        return;
    }
    
    shelf = shelf_p;
    for (i = 0; i < glob_shelves; i++)
    {
        shelf_p[i].cell = (cells *)malloc(glob_cells * sizeof(cells));
    if (shelf_p[i].cell==NULL)
    {
        myERROR();
        return;
    }

        shelf_p[i].num = i;
        for (int j = 0; j < glob_cells; j++)
        {
            shelf_p[i].cell[j].num = j;
            shelf_p[i].cell[j].item.num = 0;
            strcpy(shelf_p[i].cell[j].item.name, "\0");
        }
    }
    return;
}
int foundShelf(int shelf_num)
{
    if (shelf_num < 0 || shelf_num >= glob_shelves)
    {
        return 0;
    }
    return 1;
}
int foundCell(int cell_num)
{
    if (cell_num < 0 || cell_num >= glob_cells)
    {
        return 0;
    }
    return 1;
}
int Freecells_from(int shelf_num, int from_cell, int quant)
{
    int current_cell_num = from_cell;
    int count = 0;
    for (int i = 0; i < quant; i++)
    {
        if (shelf[shelf_num].cell[current_cell_num].item.num != 0)
        {
            return 0;
        }
        current_cell_num++;
    }
    return 1;
}
int Freecells_inShelf(int shelf_num, int quant)
{
    int count = 0;
    int index = 0;
    if (foundShelf(shelf_num) == 0)
    {
        return -1;
    }
    if (quant < 0 || quant > (glob_cells))
    {
        return -1;
    }

    for (int i = 0; i < glob_cells; i++)
    {
        if (shelf[shelf_num].cell[i].item.num == 0)
        {
            count++;
            if (count == 1)
            {
                index = i;
            }
        }
        else if (shelf[shelf_num].cell[i].item.num != 0)
        {
            count = 0;
        }
        if (count == quant && quant != 0)
        {
            return index;
        }
    }
    if (count != quant || quant == 0)
    {
        return -1;
    }
    return 0;
}
int Freecells_Anywhr2(int quant, int curr_shelf)
{
    int i;
    int j;
    int count = 0;
    int cell_index = 0;
    int shelf_index = 0;
    if (quant < 0 || quant > (glob_cells))
    {
        myERROR();
        return -1;
    }

    for (i = curr_shelf; i < glob_shelves; i++){
        count=0;
        for (j = 0; j < glob_cells; j++){
            if (shelf[i].cell[j].item.num == 0){
                count++;
                if (count == 1)
                {
                    cell_index = j;
                }
            }
            else if (shelf[i].cell[j].item.num != 0)
            {
                count = 0;
            }
            if (count == quant && quant != 0)
            {
                shelf_index = i;
                return shelf_index;
            }
        }
    }
    if (count != quant || quant == 0)
    {
        return -1;
    }
    return 0;
}
int Freecells_Anywhr(int quant)
{
    int i;
    int j;
    int count = 0;
    int cell_index = 0;
    int shelf_index = 0;
    if (quant < 0 || quant > (glob_cells))
    {
        myERROR();
        return -1;
    }

    for (i = 0; i < glob_shelves; i++){
        count=0;
        for (j = 0; j < glob_cells; j++){
            if (shelf[i].cell[j].item.num == 0){
                count++;
                if (count == 1)
                {
                    cell_index = j;
                }
            }
            else if (shelf[i].cell[j].item.num != 0)
            {
                count = 0;
            }
            if (count == quant && quant != 0)
            {
                shelf_index = i;
                return shelf_index;
            }
        }
    }
    if (count != quant || quant == 0)
    {
        return -1;
    }
    return 0;
}
void add_somewhere2(char *item_name, int quant, int curr_shelf)
{
    int shelf_to_add=Freecells_Anywhr2(quant, curr_shelf);
    int cell_to_add=Freecells_inShelf(shelf_to_add,quant);
    input_items(item_name, shelf_to_add, cell_to_add, quant);
    return;
}
void add_somewhere(char *item_name, int quant)
{
    if (Freecells_Anywhr(quant)==-1){
        New_Shelf();
    }
    int shelf_to_add=Freecells_Anywhr(quant);
    int cell_to_add=Freecells_inShelf(shelf_to_add,quant);
    input_items(item_name, shelf_to_add, cell_to_add, quant);
    return;
}
void input_items(char item_name[], int shelf_num, int cell_num, int quant)
{
    int current_cell_num = cell_num;
    char name[30] = {0};
    strcpy(name, item_name);
    for (int i = 0; i < quant; i++)
    {
        strcpy(shelf[shelf_num].cell[current_cell_num].item.name, name);
        shelf[shelf_num].cell[current_cell_num].item.num = glob_total_items + 1;
        glob_total_items++;
        last_item_num++;
        current_cell_num++;
    }
    return;
}
void New_Shelf(void)
{
    shelf = (shelves *)realloc(shelf, ++glob_shelves * sizeof(shelves));
    if (shelf==NULL){
        myERROR();
        return;
    }

    for (int i = 0; i < glob_shelves; i++)
    {
        shelf[glob_shelves-1].cell = (cells *)calloc(glob_cells, sizeof(cells));
            if (shelf[glob_shelves-1].cell==NULL)
            {
                myERROR();
                return;
            }
        shelf[glob_shelves-1].num = i;
        for (int j = 0; j < glob_cells; j++)
        {
            shelf[glob_shelves-1].cell[j].num = j;
            shelf[glob_shelves-1].cell[j].item.num = 0;
            strcpy(shelf[glob_shelves-1].cell[j].item.name, "\0");
        }
    }    
    return;
}
void Clear_Cell(int shelf_num, int cell_num)
{
    shelf[shelf_num].cell[cell_num].item.num = 0;
    strcpy(shelf[shelf_num].cell[cell_num].item.name, "\0");
    return;
}
void Swap(int shelfA, int cellA, int shelfB, int cellB)
{
    char temp_name[15] = {0};
    int temp_num;
    //put item A in Temp
    strcpy(temp_name, shelf[shelfA].cell[cellA].item.name);
    temp_num = shelf[shelfA].cell[cellA].item.num;
    //put item B in A
    strcpy(shelf[shelfA].cell[cellA].item.name, shelf[shelfB].cell[cellB].item.name);
    shelf[shelfA].cell[cellA].item.num = shelf[shelfB].cell[cellB].item.num;
    //put item Temp in B
    strcpy(shelf[shelfB].cell[cellB].item.name, temp_name);
    shelf[shelfB].cell[cellB].item.num = temp_num;
    return;
}
int shelf_of_an_item(int item_num)
{
    for (int i = 0; i < glob_shelves; i++){
        for (int j = 0; j < glob_cells; j++){
            if (shelf[i].cell[j].item.num==item_num){
                return i;
            }   
        }
    }
}
int cell_of_an_item(int item_num)
{
    for (int i = 0; i < glob_shelves; i++){
        for (int j = 0; j < glob_cells; j++){
            if (shelf[i].cell[j].item.num==item_num){
                return j;
            }   
        }
    }
}
int shelf_empty(int shelf_num)
{
    if (foundShelf(shelf_num)==0){
        printf("ERROR shelf not found");
        return -1;
    }
    if (Freecells_inShelf(shelf_num,glob_cells)!=-1){
        return 1;
    }
    return 0;
}
int last_shelf_is_empty(void)
{
    for (int i = 0; i < glob_shelves; i++){
        if (shelf_empty(i)==1){
                return 1;
             }
    }  
    return 0;
}
void Remove_last_Shelf(void)
{
    glob_shelves--;
    shelf = (shelves *)realloc(shelf, glob_shelves * sizeof(shelves));
    if (shelf==NULL){
        myERROR();
        return;
    }
    for (int i = 0; i < glob_shelves; i++)
    {
        shelf[glob_shelves-1].cell = (cells *)realloc(shelf[glob_shelves-1].cell, glob_cells * sizeof(cells));
        if (shelf[glob_shelves-1].cell==NULL){
            myERROR();
            return;
        }

        shelf[glob_shelves-1].num = i;
        for (int j = 0; j < glob_cells; j++)
        {
            shelf[glob_shelves-1].cell[j].num = j;
        }
    }    
    return;
}
void compress_shelves()
{
    for (int i = 0; i < glob_cells; i++){
        for (int i = 0; i < glob_shelves; i++){
            if (shelf_empty(i)==0){                             //case shelf [i] is not empty
                    if (Freecells_inShelf(i, 1) != -1)         //if it has at least 1 empty cell - return it's number)
                    {
                        int temp_cell=Freecells_inShelf(i, 1);
                        for (int j = temp_cell; j <= glob_cells; j++)
                        {
                            if (shelf[i].cell[j].num!=0)
                            {
                                move_item2(shelf[i].num, shelf[i].cell[j].num, shelf[i].num, shelf[i].cell[temp_cell].num);
                            }
                            
                        }
                    }
                }
            }
    }
        return;
}
void compress_cells()
{
    int emptycells_inshelf;
    int first_empty;
    for (int i = 0; i < glob_shelves-1; i++){
        if (shelf[i].cell[glob_cells-1].item.num==0){
            emptycells_inshelf= glob_cells - Freecells_inShelf(shelf[i].num, 1);
            move_item(shelf[i+1].num, shelf[i+1].cell[0].num, shelf[i].num, shelf[i].cell[glob_cells-1].num);
        }
    }
}  
void move_item2(int shelfA, int cellA, int shelfB, int cellB)
{
        if (foundShelf(shelfA) == 0 || foundShelf(shelfB) == 0)
    {
        return;
    }
    if (foundCell(cellA) == 0 || foundCell(cellB) == 0)
    {
        return;
    }
    if (shelf[shelfB].cell[cellB].item.num != 0)
    {
        return;
    }
    shelf[shelfB].cell[cellB].item.num = shelf[shelfA].cell[cellA].item.num;
    strcpy(shelf[shelfB].cell[cellB].item.name, shelf[shelfA].cell[cellA].item.name);
    Clear_Cell(shelfA, cellA);
    return;
}
//Main Functions
void add_item(char *item_name, int shelf_num, int cell_num, int quant)
{
    if (shelf_num < -1 || shelf_num >= glob_shelves)                     //case shelf_num isn't legal - error
    {
        addERROR();
        return;
    }
    if (cell_num >= glob_shelves)                                       //case cell_num isn't legal - error
    {
        addERROR();
        return;
    }
    
    if (shelf_num == -1 && cell_num != -1)                              //case only cell_num is given - error
    {
        myERROR();
        return;
    }

    if (shelf_num !=-1 && cell_num == -1)                               //case only shelf_num is given 
    {
        int new_cell_to_add = Freecells_inShelf(shelf_num,quant);
        if (new_cell_to_add != -1)                                      //if enough room on shelf - add.
        {
            input_items(item_name, shelf_num, new_cell_to_add, quant); 
            return;
        }
        else                                                            //else - add somewhere else.
        {
            if (Freecells_Anywhr2(quant,shelf_num)!= -1)
            {
                add_somewhere2(item_name, quant,shelf_num);
                return;
            }
                add_somewhere(item_name, quant);
                return;
        }
        
    }
    
    if (shelf_num==-1 && cell_num==-1)                                   //case position unspecified -FIXED!
    {
        add_somewhere(item_name, quant);                                 //add somewhere.
        return;
    }

    if (shelf_num != -1 && cell_num !=-1)                                //case position specified
    {
        int enough=Freecells_from(shelf_num, cell_num, quant);
        if (enough==1)                                                 //if enough cells - add.
        {
            input_items(item_name, shelf_num, cell_num,quant);
            return;
        }
        if (shelf[shelf_num].cell[cell_num].item.num != 0)               //case cell occupied
        {
            int new_cell_to_add = Freecells_inShelf(shelf_num,quant);
            if (new_cell_to_add != -1)                                   //if enough room on shelf - add.
            {
                input_items(item_name, shelf_num, new_cell_to_add, quant); 
                return;
            }        
            else
            {
                if (Freecells_Anywhr2(quant,shelf_num)!= -1)
            {
                add_somewhere2(item_name, quant,shelf_num);             //else to one of the next shelves.
                return;
            }
                add_somewhere(item_name,quant);                         //else add somewhere in storage.
                return;
            }
    
        }
        
        else                                                           //case position is good -add.
        {
            if (Freecells_from(shelf_num,cell_num,quant)==0)
            {
                if (Freecells_Anywhr2(quant,shelf_num)!= -1)
            {
                add_somewhere2(item_name, quant,shelf_num);             //else to one of the next shelves.
                return;
            }
                add_somewhere(item_name,quant);                         //else add somewhere in storage.
                return;
            }
            else
            {
            input_items(item_name, shelf_num, cell_num, quant);
            return;
            }
            
        }
    } 

}
void remove_item(int shelf_num, int cell_num)
{
    if (foundShelf(shelf_num) == 0)
    {
        removeERROR();
        return;
    }
    else if (foundCell(cell_num) == 0)
    {
        removeERROR();
        return;
    }
    else
    {
        if (shelf[shelf_num].cell[cell_num].item.num!=0)        //if cell Contains item, total= total -1 ;
        {
            glob_total_items--;
        }
        
        Clear_Cell(shelf_num, cell_num);
    }
    return;
}
void move_item(int shelfA, int cellA, int shelfB, int cellB)
{
    if (foundShelf(shelfA) == 0 || foundShelf(shelfB) == 0)
    {
        moveERROR();
        return;
    }
    if (foundCell(cellA) == 0 || foundCell(cellB) == 0)
    {
        moveERROR();
        return;
    }
    if (shelf[shelfB].cell[cellB].item.num != 0)
    {
        moveERROR();
        return;
    }

    shelf[shelfB].cell[cellB].item.num = shelf[shelfA].cell[cellA].item.num;
    strcpy(shelf[shelfB].cell[cellB].item.name, shelf[shelfA].cell[cellA].item.name);
    Clear_Cell(shelfA, cellA);
    return;
}
void switch_items(int shelfA, int cellA, int shelfB, int cellB)
{
    if (foundShelf(shelfA) == 0 || foundShelf(shelfB) == 0)
    {
        swapERROR();
        return;
    }
    if (foundCell(cellA) == 0 || foundCell(cellB) == 0)
    {
        swapERROR();
        return;
    }
    if (shelf[shelfA].cell[cellA].item.num == 0 || shelf[shelfB].cell[cellB].item.num == 0)
    {
        swapERROR();
    }

    Swap(shelfA, cellA, shelfB, cellB);
    return;
}
void print_item(int item_number)
{
    if (item_number < 1 || item_number > glob_total_items)
    {
        printERROR();
        return;
    }

    for (int i = 0; i < glob_shelves; i++)
    {
        for (int j = 0; j < glob_cells; j++)
        {
            if (shelf[i].cell[j].item.num == item_number)
            {
                printf("Item: %s, Number: %d, Position: [%d,%d]", shelf[i].cell[j].item.name, shelf[i].cell[j].item.num, i, j);
                printf("\n");
                return;
            }
        }
    }
    printERROR();
    return;
}
void print_storage(void)
{
    printf("Total space: %d\n", (glob_shelves * glob_cells) - glob_total_items);
    printf("Shelves: %d\n", glob_shelves);
    printf("Total items: %d\n", glob_total_items);
    for (int i = 0; i < glob_shelves; i++)
    {
        for (int j = 0; j < glob_cells; j++)
        {
            if (shelf[i].cell[j].item.num != 0)
            {
                printf("Item: %s, Number: %d, Position: [%d,%d]", shelf[i].cell[j].item.name, shelf[i].cell[j].item.num, i, j);
                printf("\n");
            }
        }
    }
    return;
}
void matrix(void)
{
    int i = 0;
    int j = 0;
    printf("\t");
    for (j = 0; j < glob_cells; j++)
    {
        printf("|%d\t", shelf[i].cell[j].num);
    }
    printf("\n");
    printf("---------------------------------------------\n");
    for (i = 0; i < glob_shelves; i++)
    {
        printf("%d\t", shelf[i].num);
        for (int j = 0; j < glob_cells; j++)
        {
            if (shelf[i].cell[j].item.num!=0)
            {
                printf("|%.3s\t", strupr(shelf[i].cell[j].item.name)); //print item name
            }
            else printf("|%.3s\t", "X");
        }
        printf("\n");
    }
    return;
}
void minimize_storage(void)
{
    int spaces = (glob_shelves*glob_cells)-glob_total_items;
    for (int i = 0; i < spaces+1; i++)
    {
        compress_shelves();                  // compresses each shelf so the items is near each other witout spaces
        compress_cells();                    // first cell of the next shelf becomes last cell in current shelf
    }
    while (last_shelf_is_empty()==1)
    {
        Remove_last_Shelf();
    }
    
    return;
}
//END
