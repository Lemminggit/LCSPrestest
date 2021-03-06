#pragma once
/*enum thisItemIs {
	THIS_IS_WEAPON,
	THIS_IS_ARMOR,
	THIS_IS_CLIP,
	THIS_IS_LOOT,
	THIS_IS_MONEY,
	THIS_IS_CLOTH,
	THIS_IS_NUM
};*/
class Item
{
public:
	Item() : number_(1) { }
	explicit Item(const ItemType& seed, int number = 1);
	// (Sub-?)Constructor to create item from xml.
	explicit Item(const std::string& inputXml);
	virtual ~Item() { }
	// Returns xml describing the item. Used when saving.
	virtual string showXml() const = 0;
	// Adds the item base class properities.
	void addBaseValues(CMarkup& xml) const;
	//
	virtual string equip_title() const = 0;
	// Create copy of item and return pointer.
	virtual Item* clone() const = 0;
	// Creates a copy of the item and divides the number between them.
	virtual Item* split(int number) = 0;
	// Use to merge two identical items. Leaves referenced item in parameter
	// empty, ie number_=0.
	virtual bool merge(Item& i) = 0;
	static bool sort_compare(Item* a, Item* b);
	virtual bool sort_compare_special(Item* other) const = 0;
	virtual bool is_same_type(const Item& i) const { return itemtypename_ == i.itemtypename_; }
	virtual thisItemIs whatIsThis() const = 0;
	virtual bool is_cloth() const { return false; }
	virtual const string& get_name() const = 0;
	const char* aan() const;
	virtual long get_fencevalue() const = 0;
	virtual bool is_good_for_sale() const { return true; } //Have one that gives an error message when suitable? -XML
	void set_number(long number) { number_ = number; }
	void increase_number(long increase) { number_ += increase; }
	void decrease_number(long decrease) { number_ -= decrease; }
	long get_number() const { return number_; }
	bool empty() const { return number_ <= 0; }
	const string& get_itemtypename() const { return itemtypename_; }
	long get_itemtypeid() const { return itemtypeid_; }
	bool no_quick_fencing() const { return false; } // Overridden in loot.h.  Try to never use at all.
protected:
	//string& get_itemtypename() { return itemtypename_; }
	//const string& get_itemtypename() const { return itemtypename_; }
	//long& itemtypeid() { return itemtypeid_; }
	//const long& itemtypeid() const { return itemtypeid_; }
	long number_;
private:
	string itemtypename_;
	long itemtypeid_;
};
