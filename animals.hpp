#ifndef ANIMALS_HPP
#define ANIMALS_HPP

struct OwnerInfo {
	std::string currentFirst;
	std::string currentLast;
	std::string currentEmail;
	std::string formerFirst;
	std::string formerLast;
	std:: string formerEmail;
};

struct AnimalInfo {
	std::string id;
	std::string animalName;
	std::string animalType;
	std::string surrenderDate;
	std::string adoptDate;
	std::string comments;
	std::string currentNum;
	std::string formerNum;
	OwnerInfo owner;
};

struct NodeType;

typedef NodeType *NodePtr;

struct NodeType {
	AnimalInfo info;
	NodePtr next;
};

#endif	// ANIMALS_HPP
