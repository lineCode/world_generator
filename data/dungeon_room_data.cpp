#include "dungeon_room_data.h"

Ref<PropData> DungeonRoomData::get_prop_data(const int index) const {
	ERR_FAIL_INDEX_V(index, _prop_datas.size(), Ref<PropData>());

	return _prop_datas.get(index);
}
void DungeonRoomData::set_prop_data(const int index, const Ref<PropData> prop_data) {
	ERR_FAIL_INDEX(index, _prop_datas.size());

	_prop_datas.set(index, prop_data);
}
void DungeonRoomData::add_prop_data(const Ref<PropData> prop_data) {
	_prop_datas.push_back(prop_data);
}
void DungeonRoomData::remove_prop_data(const int index) {
	ERR_FAIL_INDEX(index, _prop_datas.size());

	_prop_datas.remove(index);
}

int DungeonRoomData::get_prop_data_count() const {
	return _prop_datas.size();
}

Vector<Variant> DungeonRoomData::get_prop_datas() {
	Vector<Variant> r;
	for (int i = 0; i < _prop_datas.size(); i++) {
		r.push_back(_prop_datas[i].get_ref_ptr());
	}
	return r;
}
void DungeonRoomData::set_prop_datas(const Vector<Variant> &prop_datas) {
	_prop_datas.clear();
	for (int i = 0; i < prop_datas.size(); i++) {
		Ref<PropData> prop_data = Ref<PropData>(prop_datas[i]);

		_prop_datas.push_back(prop_data);
	}
}

Ref<DungeonRoom> DungeonRoomData::setup_room(int seed) {
	if (has_method("_setup_room")) {
		return call("_setup_room", seed);
	}

	return Ref<DungeonRoom>(NULL);
}

DungeonRoomData::DungeonRoomData() {

}
DungeonRoomData::~DungeonRoomData() {

}

void DungeonRoomData::_bind_methods() {
	BIND_VMETHOD(MethodInfo(PropertyInfo(Variant::OBJECT, "room", PROPERTY_HINT_RESOURCE_TYPE, "DungeonRoom"), "_setup_room", PropertyInfo(Variant::INT, "seed")));

	ClassDB::bind_method(D_METHOD("setup_room", "seed"), &DungeonRoomData::setup_room);

	ClassDB::bind_method(D_METHOD("get_prop_data", "index"), &DungeonRoomData::get_prop_data);
	ClassDB::bind_method(D_METHOD("set_prop_data", "index", "data"), &DungeonRoomData::set_prop_data);
	ClassDB::bind_method(D_METHOD("add_prop_data", "prop_data"), &DungeonRoomData::add_prop_data);
	ClassDB::bind_method(D_METHOD("remove_prop_data", "index"), &DungeonRoomData::remove_prop_data);

	ClassDB::bind_method(D_METHOD("get_prop_data_count"), &DungeonRoomData::get_prop_data_count);

	ClassDB::bind_method(D_METHOD("get_prop_datas"), &DungeonRoomData::get_prop_datas);
	ClassDB::bind_method(D_METHOD("set_prop_datas", "prop_datas"), &DungeonRoomData::set_prop_datas);
	ADD_PROPERTY(PropertyInfo(Variant::ARRAY, "prop_datas", PROPERTY_HINT_NONE, "17/17:PropData", PROPERTY_USAGE_DEFAULT, "PropData"), "set_prop_datas", "get_prop_datas");
}