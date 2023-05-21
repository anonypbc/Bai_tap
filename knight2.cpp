    #include "knight2.h"

    /* * * BEGIN implementation of class BaseBag * * */
    bool BaseBag::insertFirst(BaseItem * item) {
        if (count < capacity) {
            Node* new_node = new Node;
            new_node->item = item;
            new_node->next = head;
            head = new_node;
            return true;
        }
        return false; 
    }
    BaseItem *BaseBag::get(ItemType itemType){
        Node* current = head;
        Node* prev = nullptr;
        while (current) {
            if (current->item->getItem() == itemType) {
                if (prev) {
                    prev->next = current->next;
                } else {
                    head = current->next;
                }
                BaseItem* item = current->item;
                delete current;
                return item;
            }
            prev = current;
            current = current->next;
            if (count < capacity) {
                break; 
            }
        }
        
        return nullptr;
    }
    string BaseBag::toString() const {
        string result = "Bag[count=";
        int count = 0;
        string items = "";
        Node* current = head;
        while (current) {
            count++;
            switch (current->item->getItem()) {
                case ANTIDOTE:
                    items += "Antidote";
                    break;
                case PHOENIX_I:
                    items += "PhoenixI";
                    break;
                case PHOENIX_II:
                    items += "PhoenixII";
                    break;
                case PHOENIX_III:
                    items += "PhoenixIII";
                    break;
                case PHOENIX_IV:
                    items += "PhoenixIV";
                    break;
            }
            if (current->next) {
                items += ",";
            }
            current = current->next;
        }
        result += to_string(count) + ";" + items + "]";
        return result;
    }
    class Antidote : public BaseItem{
    public:
        Antidote() {
            Item = ANTIDOTE;
        };
        bool canUse(BaseKnight *knight) override {
            return knight->getPoison();
        }
        void use(BaseKnight *knight) override {
            knight ->setPoison(false);
            bool result = knight->getPoison();
        }
        string toString(){ 
            return "Antidote";
        }
    };
    class PhoenixDownI : public BaseItem{
    public:
        PhoenixDownI() {
            Item = PHOENIX_I;
        };
        bool canUse(BaseKnight *knight) override {
            if (knight ->getHP() <= 0) {
                return knight ->getPoison();
            }
            else {
                knight->setPoison(false);
                return knight ->getPoison();
            }
        }
        void use(BaseKnight *knight) override {
            knight ->setPoison(false);
            knight ->setHP(knight ->getMaxHP());
        }
        string toString(){ 
            return "PhoenixI";
        }
    };
    class PhoenixDownII : public BaseItem {
    public:
        PhoenixDownII() {
            Item = PHOENIX_II;
        }
        bool canUse(BaseKnight *knight) override{
            int max_temp = knight ->getHP();
            if (knight ->getHP() < (max_temp/4)) {
                return knight ->getPoison();
            }
        }
        void use(BaseKnight *knight) override {
            knight ->setPoison(false);
            knight ->setHP(knight ->getMaxHP());
        }
        string toString(){ 
            return "PhoenixII";
        }
    };
    class PhoenixDownIII : public BaseItem {
    public:
        PhoenixDownIII() {
            Item = PHOENIX_III;
        }
        bool canUse(BaseKnight *knight) override{
            int max_temp = knight ->getHP();
            if (knight ->getHP() < (max_temp/3)) {
                return knight ->getPoison();
            }
        }
        void use(BaseKnight *knight) override {
            knight ->setPoison(false);
            bool result = knight ->getPoison();
            knight ->setHP((knight ->getMaxHP())/4);
        }
        string toString(){ 
            return "PhoenixIII";
        }
    };
    class PhoenixDownIV : public BaseItem {
    public:
        PhoenixDownIV() {
            Item = PHOENIX_IV;
        }
        bool canUse(BaseKnight *knight) override{
            int max_temp = knight ->getHP();
            if (knight ->getHP() < (max_temp/2)) {
                return knight ->getPoison();
            }
        }
        void use(BaseKnight *knight) override {
            knight ->setPoison(false);
            bool result = knight ->getPoison();
            knight ->setHP((knight ->getMaxHP())/5);
        }
        string toString(){ 
            return "PhoenixIV";
        }
    };
    class PaladinBag : public BaseBag{
    public:
        PaladinBag(BaseKnight *knight, int phoenix_I, int antidote) : BaseBag(knight, phoenix_I, antidote) {
            this ->capacity = 0;
            for(int i = 0; i < phoenix_I;i++) {
                insertFirst(new PhoenixDownI());
                count++;
                if (count == capacity) {
                    break; 
                }
            }
            for(int x = 0; x <antidote; x++) {
                insertFirst(new Antidote());
                count++;
                if (count == capacity) {
                    break; 
                }
            }
        };
    };
    class DragonBag : public BaseBag {
    public:
        DragonBag(BaseKnight *dragon, int phoenix_I, int antidote) : BaseBag(dragon, phoenix_I, antidote) {
            this ->capacity = 14; 
            for(int x = 0; x < phoenix_I;x++) {
                insertFirst(new PhoenixDownI());
                count++;
                if (count == capacity) {
                    break; 
                }
            }
        }
    };
    class LancelotBag : public BaseBag {
    public:
        LancelotBag(BaseKnight *lancelot, int phoenix_I, int antidote) : BaseBag(lancelot, phoenix_I, antidote) {
            this ->capacity = 16;
            for (int i = 0; i < phoenix_I; i++) {
                insertFirst(new PhoenixDownI);
                count++;
                if (count == capacity) {
                    break; 
                }
            }
            // for(int x = 0; x <antidote; x++) {
            //     insertFirst(new Antidote());
            //     count++;
            //     if (count == capacity) {
            //         break; 
            //     }
            // }
            
        }
    };
    class RoundTableBag : public BaseBag {
    public:
        RoundTableBag(BaseKnight *round, int phoenix_I, int antidote) : BaseBag(round, phoenix_I, antidote) {
            this -> capacity = 19;
            this ->count = 0; 
            for (int i = 0; i < phoenix_I; i++) {
                insertFirst(new PhoenixDownI);
                count++;
                if (count == capacity) {
                    break; 
                }
            }
        }
    };
    void BaseBag::remove(){
        if(count == 0) return;
        count--;
        Node* temp = head;
        head = head->next;
        delete temp->item;
        delete temp;
    }
    BaseBag::~BaseBag() {
        while(count){
            count--;
            Node* temp = head;
            head = head->next;
            delete temp->item;
            delete temp;
        }
    }
    /* * * END implementation of class BaseBag * * */

    /* * * BEGIN implementation of class BaseKnight * * */
    void BaseKnight::setBag(BaseBag *bag){
        this ->bag = bag;
    }

    int BaseKnight::getID() {
        return id;
    }
    int BaseKnight::getMaxHP() {
        return maxhp;
    }
    void BaseKnight::setHP(int hp) {
        this ->hp = hp;
    }
    int BaseKnight::getHP() {
        return hp; 
    }
    void BaseKnight::setGil(int gil) {
        this ->gil = gil;
    }
    int BaseKnight::getGil() {
        return gil;
    }
    int BaseKnight::getPhoenix() {
        return PhoenixDownI;
    }
    int BaseKnight::getAnti() {
        return antidote;
    }
    int BaseKnight::getType() {
        return knightType;
    }
    bool BaseKnight::getPoison() {
        return isPoisoned; 
    }
    void BaseKnight::setPoison(bool Poison) {
        this ->isPoisoned = Poison;
    }
    int BaseKnight::getLev() {
        return level;
    }
    void BaseKnight::setLev(int lev) {
        this ->level = lev;
    }
    int BaseKnight::getExcessiveGil() {
        return excessiveGil;
    }
    void BaseKnight::setExcessiveGil(int excessiveGil) {
        this ->excessiveGil = excessiveGil;

        
    }
    int BaseKnight::getBaseDame() {
        return KnightBaseDame;
    }
    BaseKnight::~BaseKnight() {
        delete bag;  
    }
    class PaladinKnight : public BaseKnight {
    public:
            PaladinKnight(int id, int maxhp, int level, int gil, int antidote, int PhoenixDownI) : BaseKnight (id, maxhp, level, gil, antidote, PhoenixDownI) {
                this -> knightType = PALADIN; 
                this ->KnightBaseDame = 0.06;
            } 
            bool fight(BaseOpponents *opnt);
    };
    class LancelotKnight : public BaseKnight {
    public:
        LancelotKnight(int id,int maxhp,int level,int gil,int antidote, int PhoenixDownI) : BaseKnight(id,maxhp,level,gil,antidote,PhoenixDownI){
            this -> knightType = LANCELOT; 
            this ->KnightBaseDame = 0.05;
        }
        bool fight(BaseOpponents *opnt);
    };
    class DragonKnight : public BaseKnight {
        public:
            DragonKnight(int id, int maxhp, int level, int gil, int antidote, int PhoenixDownI) : BaseKnight (id, maxhp, level, gil, antidote, PhoenixDownI) {
                this -> knightType = DRAGON; 
                this ->KnightBaseDame = 0.075;
            } 
            bool fight(BaseOpponents *opnt);
    };
    class NormalKnight : public BaseKnight {
        public:
            NormalKnight(int id, int maxhp, int level, int gil, int antidote, int PhoenixDownI) : BaseKnight (id, maxhp, level, gil, antidote, PhoenixDownI) {
                this -> knightType = NORMAL;
            }
            bool fight(BaseOpponents *opnt);
    };
    //check prime
    bool isPrime(int n) {
        if (n <= 1) {
            return false;
        }
        for (int i = 2; i <= sqrt(n); i++) {
            if (n % i == 0) {
                return false;
            }
        }
        return true;
    }

    //check pythagoras 
    bool isPythagoras(int hp1) {
        if (hp1 < 100) {
            return false;
        }
        // else if (hp1 >= 100) {

        // }
        int numbers[3];
        string hp_str = to_string(hp1); 
        for (int i = 0; i < 3; i++) {
            numbers[i] = stoi(hp_str.substr(i, 1));
        }
        int max = 0;
        for (int i = 0; i < 3; i++) {
            if (numbers[i] > max) {
                max = numbers[i]; 
            } 
        }
        //cout << max << endl;
        int smaller[2];
        int c = 0;
        for (int number : numbers) {
            if (number == max) {
                continue;
            }
            smaller[c] = number;
            c++; 
        }
        int n1,n2;
        n1 = smaller[0];
        n2 = smaller[1]; 
        int firstSum = (n1*n1) + (n2*n2);
        int secSum = max*max;
        if (secSum == firstSum) {
            return true;
        }
        else {
            return false; 
        }
    }
    BaseKnight *BaseKnight::create(int id, int maxhp, int level, int gil, int antidote, int phoenixdownI) {
        if (maxhp >= 100) {
            if(isPrime(maxhp)) {
                return new PaladinKnight(id, maxhp, level, gil, antidote, phoenixdownI); 
            } 
            else if (maxhp == 888) {
                return new LancelotKnight(id, maxhp, level, gil, antidote,phoenixdownI); 
            }
            else if (isPythagoras(maxhp)) {
                return new DragonKnight(id, maxhp, level, gil, antidote, phoenixdownI); 
            }
            else {
                return new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI); 
            }        
        }
        else {
            return new NormalKnight(id, maxhp, level, gil, antidote, phoenixdownI);
        }
    }; 
    bool BaseKnight::fight(BaseOpponents * opponent){
        if(this->isPoisoned){
            this->bag->get(ANTIDOTE);
            if(this->isPoisoned){
                this->isPoisoned = false;
                this->bag->remove();
                this->bag->remove();
                this->bag->remove();
                this->setHP(this->hp -  10);
            }
        }    
        if(this->hp <= 0 && this->gil >= 100){
            this->hp = this->maxhp / 2;
            this->gil -= 100;

        }
        return this->hp > 0;
    }
    string BaseKnight::toString() const {
        string typeString[4] = {"PALADIN", "LANCELOT", "DRAGON", "NORMAL"};
        // inefficient version, students can change these code
        //      but the format output must be the same
        string s("");
        s += "[Knight:id:" + to_string(id) 
            + ",hp:" + to_string(hp) 
            + ",maxhp:" + to_string(maxhp)
            + ",level:" + to_string(level)
            + ",gil:" + to_string(gil)
            + "," + bag->toString() + "]"  // fixed here
            + ",knight_type:" + typeString[knightType]
            + "]";
        return s;
    }

    /* * * END implementation of class BaseKnight * * */
    //Implementation of Opponent 
        
    BaseOpponents * BaseOpponents::create(int eve_code, OpponentType opponentType){
        BaseOpponents * opponent;
        if(opponentType == MadBear) opponent = new MadBearO();
        else if(opponentType == Bandit) opponent = new BanditO();
        else if(opponentType == LordLupin) opponent = new LordLupinO();
        else if(opponentType == Elf) opponent = new ElfO();
        else if(opponentType == Troll) opponent = new TrollO();
        else if(opponentType == Tornbery) opponent = new TornberyO();
        else if(opponentType == QueenOfCards) opponent = new QueenOfCardsO();
        else if(opponentType == NinaDeRings) opponent = new NinaDeRingsO();
        else if(opponentType == DurianGarden) opponent = new DurianGardenO();
        else if(opponentType == OmegaWeapon) opponent = new OmegaWeaponOpponent();
        else if(opponentType == Hades) opponent = new HadesOpponent();
        else return nullptr;
        // opponent->i = i;
        return opponent;
    }

    OpponentType MadBearO::Type(){return MadBear;}
    void MadBearO::KnightStatus(BaseKnight* knight){
        int levelO = (this->i + this->Type())%10 + 1;
        if(levelO <= knight->getLev()) knight->setGil(knight->getGil() + 100);
        else knight->setHP(knight->getHP() - 10 * (levelO - knight->getLev()));    
    }
    OpponentType BanditO::Type(){return Bandit;}
    void BanditO::KnightStatus(BaseKnight* knight){
        int levelO = (this->i + this->Type())%10 + 1;
        if(levelO <= knight->getLev()) knight->setGil(knight->getGil() + 150);
        else knight->setHP(knight->getHP() - 15 * (levelO - knight->getLev()));
    }


    OpponentType LordLupinO::Type(){return LordLupin;}
    void LordLupinO::KnightStatus(BaseKnight* knight){
    int levelO = (this->i + this->Type())%10 + 1;
        if(levelO <= knight->getLev()) knight->setGil(knight->getGil() + 450);
        else knight->setHP(knight->getHP() - 45 * (levelO - knight->getLev()));
    }


    OpponentType ElfO::Type(){return Elf;}
    void ElfO::KnightStatus(BaseKnight* knight){
        int levelO = (this->i + this->Type())%10 + 1;
        if(levelO <= knight->getLev()) knight->setGil(knight->getGil() + 750);
        else knight->setHP(knight->getHP() - 75 * (levelO - knight->getLev()));
    }

    OpponentType TrollO::Type(){return Troll;}
    void TrollO::KnightStatus(BaseKnight* knight){
    int levelO = (this->i + this->Type())%10 + 1;
        if(levelO <= knight->getLev()) knight->setGil(knight->getGil() + 800);
        else knight->setHP(knight->getHP() - 95 * (levelO - knight->getLev()));
    }

    OpponentType TornberyO::Type(){return Tornbery;}
    void TornberyO::KnightStatus(BaseKnight* knight){

        int levelO = (this->i + this->Type())%10 + 1;
        if(levelO <= knight->getLev()) knight->setLev(knight->getLev() + 1);
        else knight->setPoison(true);
    }


    OpponentType QueenOfCardsO::Type(){return QueenOfCards;}
    void QueenOfCardsO::KnightStatus(BaseKnight* knight){
        int levelO = (this->i + this->Type())%10 + 1;
        if(levelO <= knight->getLev()) knight->setGil(knight->getGil() * 2);
        else knight->setGil(knight->getGil() / 2);
    }


    OpponentType NinaDeRingsO::Type(){return NinaDeRings;}
    void NinaDeRingsO::KnightStatus(BaseKnight* knight){
        if(knight->getGil() >= 50 && knight->getHP() < knight->getMaxHP()/3){
            knight->setGil(knight->getGil() - 50);
            knight->setHP(knight->getHP() + knight->getMaxHP()/5);
        }
    }


    OpponentType DurianGardenO::Type(){return DurianGarden;}
    void DurianGardenO::KnightStatus(BaseKnight* knight){
        knight->setHP(knight->getMaxHP());
    }

    OpponentType OmegaWeaponOpponent::Type(){return OmegaWeapon;}
    void OmegaWeaponOpponent::KnightStatus(BaseKnight* knight){
        if(BaseOpponents::isWinOmegaWeapon) return;

        else if(false){
            BaseOpponents::isWinOmegaWeapon = true;
            knight->setGil(999);
        }
        else knight->setHP(0);
    }

    OpponentType HadesOpponent::Type(){return Hades;}
    void HadesOpponent::KnightStatus(BaseKnight* knight){
        if(BaseOpponents::isWinHades) return;
        else if(knight->getLev() == 10){
            BaseOpponents::isWinHades = true;
        }
        else {
            knight->setHP(0);
            BaseOpponents::isWinHades = false; 
        }
    }

    bool BaseOpponents::isWinHades = false;
    bool BaseOpponents::isWinOmegaWeapon = false;
    bool PaladinKnight::fight(BaseOpponents * opnt) {
        if(opnt->Type() == 1) {
            if (this ->getGil() < 999) {
                this->setGil(this->getGil() + 100);
            }
            else {
                this ->setExcessiveGil((this ->getGil()) - 999); 
            }
        }
        else if(opnt->Type() == 2) {
            if (this ->getGil() < 999) {
                this->setGil(this->getGil() + 150);
            }
            else {
                this ->setExcessiveGil((this ->getGil()) - 999); 
            }
        }
        else if(opnt->Type() == 3) {
            if (this ->getGil() < 999) {
                this->setGil(this->getGil() + 450);
            }
            else {
                this ->setExcessiveGil((this ->getGil()) - 999); 
            }
        }
        else if(opnt->Type() == 4) {
            if (this ->getGil() < 999) {
                this->setGil(this->getGil() + 750);
            }
            else {
                this ->setExcessiveGil((this ->getGil()) - 999); 
            }
        }
        else if(opnt->Type() == 5) {
            if (this ->getGil() < 999) {
                this->setGil(this->getGil() + 800);
            }
            else {
                this ->setExcessiveGil((this ->getGil()) - 999); 
            }
        }
        else if(opnt->Type() == NinaDeRings){
            if(this->getHP() < this->getMaxHP() / 3){
                this->setHP(this->getHP() + (this->getMaxHP())/5);
            } 
        } 
        else if(opnt->Type() == QueenOfCards) {
            int Gil_first = this->gil;
            opnt->KnightStatus(this);
            if (Gil_first < this ->getGil()) {
                this ->setGil(Gil_first);
            }
        }
        else if(opnt->Type() == Hades && this->level >= 8){
            BaseOpponents::isWinHades = true;
        }
        else {
            opnt ->KnightStatus(this);
        }
        return BaseKnight::fight(opnt);
    }
    bool LancelotKnight::fight(BaseOpponents *opnt) {
        if(opnt->Type() == 1) {
            this->setGil(this->getGil() + 100);
            if (this ->getGil() > 999) {
                this ->setGil(999);
                this ->setExcessiveGil((this ->getGil()) - 999); 
            }
        }
        else if(opnt->Type() == 2) {
            this->setGil(this->getGil() + 150);
            if (this ->getGil() > 999) {
                this ->setGil(999);
                this ->setExcessiveGil((this ->getGil()) - 999); 
            }
        }
        else if(opnt->Type() == 3) {
            this->setGil(this->getGil() + 450);
            if (this ->getGil() > 999) {
                this ->setGil(999);
                this ->setExcessiveGil((this ->getGil()) - 999); 
            }
        }
        else if(opnt->Type() == 4) {
            this->setGil(this->getGil() + 750);
            if (this ->getGil() > 999) {
                this ->setGil(999);
                this ->setExcessiveGil((this ->getGil()) - 999); 
            }
        }
        else if(opnt->Type() == 5) {
            this->setGil(this->getGil() + 800);
            if (this ->getGil() > 999) {
                this ->setGil(999);
                this ->setExcessiveGil((this ->getGil()) - 999); 
            }
        }
        else opnt->KnightStatus(this);
        return BaseKnight::fight(opnt);
    }
    bool DragonKnight::fight(BaseOpponents *opnt) {
        if(opnt->Type() == OmegaWeapon){
            if(!BaseOpponents::isWinOmegaWeapon){
                level = 10;
                gil = 999;
                BaseOpponents::isWinOmegaWeapon = true;
            }
        }
        else opnt->KnightStatus(this); 

        this->setPoison(false);
        return BaseKnight::fight(opnt);
    }
    bool NormalKnight::fight(BaseOpponents *opnt) {
        if(opnt->Type() == OmegaWeapon){
            if(BaseOpponents::isWinOmegaWeapon) return true;
            else if(level == 10 && maxhp == hp){
                gil = 999;
                BaseOpponents::isWinOmegaWeapon = true;
            }
            else this->setHP(0);
        }
        else opnt->KnightStatus(this);
        return BaseKnight::fight(opnt);
    }
    // End of Opponent 
    /* * * BEGIN implementation of class ArmyKnights * * */

ArmyKnights::ArmyKnights(const string & file_armyknights) {
    PaladinShield= LancelotSpear= GuinevereHair= ExcaliburSword = false;
    ifstream army(file_armyknights);
        army >> count_knight;
        army.ignore();
        knight = new BaseKnight*[count_knight];
        
        int count = 0;
        while(getline(army,kn)){
            info[count] = kn;
            ++count;
        }
        for (int i = 0; i < count_knight; i++) {
            std::istringstream iss(info[i]);
            int maxhp, level, phoenixdownI, gil, antidote;
            
            int id = i+1;
            iss >> maxhp >> level >> phoenixdownI >> gil >> antidote;
            
            knight[i] = BaseKnight::create(id, maxhp, level, gil,antidote, phoenixdownI);
            if(knight[i]->getType() == DRAGON) {
                knight[i]->setBag(new DragonBag(knight[i], knight[i]->getPhoenix(),knight[i]->getAnti()));
            }
            else if(knight[i]->getType() == PALADIN) {
                knight[i]->setBag(new PaladinBag(knight[i], knight[i]->getPhoenix(),knight[i]->getAnti()));
            }
            else if(knight[i]->getType() == LANCELOT) {
                knight[i]->setBag(new LancelotBag(knight[i], knight[i]->getPhoenix(),knight[i]->getAnti()));
            }
            else {
                knight[i]->setBag(new RoundTableBag(knight[i], knight[i]->getPhoenix(),knight[i]->getAnti()));
            }
        }

}

bool ArmyKnights::fight(BaseOpponents*opponent) {
    while(count_knight){
        BaseKnight * lknight = lastKnight();
        if(lknight->fight(opponent)){
            for(int i = count_knight - 1; i >= 0; i--){                    
                if(knight[i]->getExcessiveGil() == 0 || i == 0)  break;
                knight[i-1]->setGil(knight[i]->getExcessiveGil() + knight[i-1]->getGil());
            }
            break;
        }
        count_knight--;
        delete lknight;
        break;
    }
    delete opponent;
    return count_knight;
}

bool ArmyKnights::adventure(Events * events){
for(int i = 0; i < events->count(); i++){
        int count_event = events->get(i);
        if(count_event >= 1 && count_event <= 11){
            this->fight(BaseOpponents::create(i,OpponentType(count_event)));
            if(BaseOpponents::isWinHades){
                if (this ->PaladinShield == false) {
                    this ->PaladinShield = true;
                }
            }
        }
        else if (count_event == 95) {
            this ->PaladinShield = true;
        }
        else if (count_event == 96) {
            this ->LancelotSpear = true;
        }
        else if (count_event == 97) {
            this ->GuinevereHair = true;
        }
        else if(count_event == 98 && PaladinShield && LancelotSpear && GuinevereHair){
            this->ExcaliburSword = true;
        }
        // else if(count_event == 112) {
        //     if ()
        // }
        else if(count_event == 99){
            if(ExcaliburSword){
                this->printInfo();
                return true; 
            }
            if(!GuinevereHair || !LancelotSpear || !PaladinShield){
                for(int i = 0; i < count_knight ; i++) {
                    delete knight[i];
                }
                count_knight = 0;
            }
            else{
                int HpUltimecia = 5000;

                BaseKnight * last = NULL;
                int Normal = 0;

                while(count_knight){
                    BaseKnight * kn = lastKnight();
                    HpUltimecia -= kn->getBaseDame();

                    if(kn->getBaseDame() == 0) {
                        Normal+=1;
                    };

                    if(kn->getBaseDame() == 0 && !last){
                        last = kn;
                        count_knight--;
                        continue;
                    }

                    if(HpUltimecia <= 0){
                        count_knight += Normal;
                        if(last) knight[count_knight - 1] = last;
                        this->printInfo();
                        if(last) delete last;
                        count_knight -= Normal;

                        return true;
                    }

                    delete knight;
                    count_knight--;
                }
                if(last) delete last;
            }
            this->printInfo();
            return false;            
        }

        this ->printInfo();
    
        if(count_knight == 0) return false;
    }
    
    return true;    
}
void ArmyKnights::printInfo() const {
    cout << "No. knights: " << this->count();
        if (this->count() > 0) {
            BaseKnight * lknight = lastKnight(); // last knight
            cout << ";" << lknight->toString();
            
        }
        cout << ";PaladinShield:" << this->hasPaladinShield()
            << ";LancelotSpear:" << this->hasLancelotSpear()
            << ";GuinevereHair:" << this->hasGuinevereHair()
            << ";ExcaliburSword:" << this->hasExcaliburSword()
            << endl
            << string(50, '-') << endl;
}

void ArmyKnights::printResult(bool win) const {
    cout << (win ? "WIN" : "LOSE") << endl;
}
BaseKnight * ArmyKnights::lastKnight() const{ return this ->knight[count_knight - 1];}
bool ArmyKnights::hasPaladinShield () const {
    return PaladinShield;
}
bool ArmyKnights::hasLancelotSpear() const{
    return LancelotSpear;
}
bool ArmyKnights::hasGuinevereHair() const{
    return GuinevereHair;
}
bool ArmyKnights::hasExcaliburSword() const{
    return ExcaliburSword;
}
ArmyKnights::~ArmyKnights() {
    delete knight;
}
    /* * * END implementation of class ArmyKnights * * */

    /* * * BEGIN implementation of class KnightAdventure * * */
    KnightAdventure::KnightAdventure(){     
        armyKnights = nullptr;
        events = nullptr;
    };
    KnightAdventure::~KnightAdventure(){
        delete armyKnights;
        delete events; 
    }; 
    void KnightAdventure::loadArmyKnights(const string & file){
        armyKnights = new ArmyKnights(file);
    };
    void KnightAdventure::loadEvents(const string &file){
        events = new Events(file);
    };
    void KnightAdventure::run(){
        BaseOpponents::isWinOmegaWeapon = BaseOpponents::isWinHades = false;
        armyKnights->printResult(armyKnights->adventure(events));    
    };

    /* * * END implementation of class KnightAdventure * * */