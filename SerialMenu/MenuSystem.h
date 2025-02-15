
// include the library code:
#include <LiquidCrystal.h>

// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

typedef struct MenuItem *pMenuItem;
typedef struct MenuSystem *pMenuSystem;
   
struct  MenuItem{
  String text;
  byte action;
  pMenuSystem childMenu;
  MenuItem():childMenu(0){};
  };

struct MenuSystem{
  public:
  MenuItem* items;
  pMenuSystem parentMenu;
  MenuSystem():parentMenu(0){}
  byte count;
  };

class MenuIterator{
  public:
  MenuSystem* currentLevel;
  int currentItem;
  void GoInto(MenuSystem* level){ currentLevel = level;};
  void Print(){
    lcd.clear();
    lcd.setCursor(0, 1);

    lcd.print("{");lcd.print(currentItem);lcd.print("}");
    lcd.print(currentLevel->items[currentItem].text);
    }

  void Select(){
    if(currentItem > (currentLevel->count -1)){ 
      lcd.print("unexpected selection");
      Print();
    }else{
      DoAction(currentLevel, currentItem);
    }
  }
  void MoveDown(){
    currentItem++;
    if(currentItem > (currentLevel->count -1)) currentItem = 0;
    Print();
  }
  void (*DoAction)(MenuSystem* level, int);
  void connectActions(void (*_DoAction)(MenuSystem*,int)){DoAction=_DoAction;};
};
