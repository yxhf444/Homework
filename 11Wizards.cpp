#include <iostream>
#include <vector>
#include <string>
#include <memory>

class MagicSpell {
private:
    std::string name;
    int power;
    std::vector<std::string> effects;

public:
    MagicSpell(const std::string& name = "None", int power = 0,
               const std::vector<std::string>& effs = {})
        : name(name), power(power), effects(effs) {}

    ~MagicSpell() = default;

    MagicSpell(const MagicSpell& other)
        : name(other.name), power(other.power), effects(other.effects) {}

    MagicSpell& operator=(const MagicSpell& other) {
        if (this != &other) {
            name = other.name;
            power = other.power;
            effects = other.effects;
        }
        return *this;
    }

    MagicSpell(MagicSpell&& other) noexcept
        : name(std::move(other.name)),
          power(other.power),
          effects(std::move(other.effects)) {
        other.power = 0;
    }

    MagicSpell& operator=(MagicSpell&& other) noexcept {
        if (this != &other) {
            name = std::move(other.name);
            power = other.power;
            effects = std::move(other.effects);
            other.power = 0;
        }
        return *this;
    }

    void newEffect(const std::string& effect) {
        effects.push_back(effect);
    }

    void print() const {
        std::cout << "Spell: " << name  << ", Power: " << power << ", Effects: " << effects.size() << std::endl;
    }

    const std::string& getName() const { return name; }
    int getPower() const { return power; }
    const std::vector<std::string>& getEffects() const { return effects; }
};

class Wizard {
private:
    std::string name;
    std::unique_ptr<MagicSpell> spell;

public:
    Wizard(const std::string& name) : name(name) {}

    ~Wizard()= default;

    void newSpell(const std::string& name, int power, const std::vector<std::string>& effects) {
        spell = std::make_unique<MagicSpell>(name, power, effects);
    }

    std::unique_ptr<MagicSpell> moveSpell() {
        return std::move(spell);
    }

    void receiveSpell(std::unique_ptr<MagicSpell> s) {
        spell = std::move(s);
    }

    void castSpell() const {
        if (spell) {
            std::cout << name << " casts:\n";
            spell->print();
        } else {
            std::cout << name << " has no spell!\n";
        }
    }

    const std::string& getName() const { return name; }
};

class Team {
private:
    std::string name;
    std::vector<std::shared_ptr<Wizard>> members;

public:
    Team(const std::string& name = "Team") : name(name) {}

    ~Team()= default;

    void addMember(std::shared_ptr<Wizard> w) {
        members.push_back(std::move(w));
    }

    void showUseCount(const std::shared_ptr<Wizard>& w) const {
        std::cout << "Use count for " << w->getName() << ": " << w.use_count() << "\n";
    }

    void perform() const {
        std::cout << "\nTeam " << name << " performs:\n";
        for (const auto& w : members) {
            w->castSpell();
        }
    }
};

class Spectator {
private:
    std::string name;
    std::weak_ptr<Wizard> fav;

public:
    Spectator(const std::string& name) : name(name) {}

    void setFavorite(const std::shared_ptr<Wizard>& w) {
        fav = w;
    }

    void watch() const {
        if (auto w = fav.lock()) {
            std::cout << "Spectator " << name << " watches " << w->getName() << "!\n";
        } else {
            std::cout << "Spectator " << name << " lost their favorite wizard!\n";
        }
    }
};


void testRuleOfFive() {
    std::cout << "\nTEST RULE OF FIVE\n";
    MagicSpell s1("Fireball", 10, {"burn"});
    MagicSpell s2 = s1;
    MagicSpell s3("Ice", 8);
    s3 = s1;
    MagicSpell s4 = std::move(s2);
    MagicSpell s5("Light");
    s5 = std::move(s3);
    s5.print();
}

void testUniquePtr() {
    std::cout << "\nTEST UNIQUE PTR\n";
    Wizard w1("Merlin");
    w1.newSpell("Fireball", 12, {"burn", "explode"});

    Wizard w2("Gandalf");
    w2.receiveSpell(w1.moveSpell());

    w1.castSpell();
    w2.castSpell();
}

void testSharedPtr() {
    std::cout << "\nTEST SHARED PTR\n";
    auto w = std::make_shared<Wizard>("Elrond");
    w->newSpell("Heal", 10, {"restore"});

    std::cout << "Use count before team: " << w.use_count() << "\n";

    Team t("CoolWizards");
    t.addMember(w);
    std::cout << "Use count after adding to team: " << w.use_count() << "\n";

    t.perform();
}

void testWeakPtr() {
    std::cout << "\nTEST WEAK PRT\n";
    auto w = std::make_shared<Wizard>("Dumbledore");
    w->newSpell("Light", 15, {"illuminate"});

    Spectator s("Harry");
    s.setFavorite(w);
    s.watch();

    w.reset();
    s.watch();
}

int main() {
    testRuleOfFive();
    testUniquePtr();
    testSharedPtr();
    testWeakPtr();

    std::cout << "\nALL TESTS COMPLETED\n";
    return 0;
}