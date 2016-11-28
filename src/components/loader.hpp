#pragma once

#include <rltk.hpp>
#include "components.hpp"

template<typename T>
void inner_loader(rltk::xml_node * node, std::size_t entity_id) {
    T component;
    component.from_xml(node);
    rltk::entity(entity_id)->assign(std::move(component));
}

void component_loader_xml(rltk::xml_node * node, std::size_t entity_id, std::string xml_identity) {
    std::cout << xml_identity << "\n";
    if (xml_identity == "available_missions_t") {
        inner_loader<available_missions_t>(node, entity_id);
    } else if (xml_identity == "blocker_t") {
        inner_loader<blocker_t>(node, entity_id);
    } else if (xml_identity == "coffee_machine") {
        inner_loader<coffee_machine>(node, entity_id);
    } else if (xml_identity == "despair_attack_t") {
        inner_loader<despair_attack_t>(node, entity_id);
    } else if (xml_identity == "logger_t") {
        inner_loader<logger_t>(node, entity_id);
    } else if (xml_identity == "map_t") {
        inner_loader<map_t>(node, entity_id);
    } else if (xml_identity == "mission_t") {
        inner_loader<mission_t>(node, entity_id);
    } else if (xml_identity == "name_t") {
        inner_loader<name_t>(node, entity_id);
    } else if (xml_identity == "nuisance_ai") {
        inner_loader<nuisance_ai>(node, entity_id);
    } else if (xml_identity == "player_t") {
        inner_loader<player_t>(node, entity_id);
    } else if (xml_identity == "position_t") {
        inner_loader<position_t>(node, entity_id);
    } else if (xml_identity == "printer_t") {
        inner_loader<printer_t>(node, entity_id);
    } else if (xml_identity == "renderable_t") {
        inner_loader<renderable_t>(node, entity_id);
    } else if (xml_identity == "server_t") {
        inner_loader<server_t>(node, entity_id);
    } else if (xml_identity == "static_ai") {
        inner_loader<static_ai>(node, entity_id);
    } else if (xml_identity == "switch_t") {
        inner_loader<server_t>(node, entity_id);
    } else if (xml_identity == "viewshed_t") {
        inner_loader<viewshed_t>(node, entity_id);
    } else if (xml_identity == "computer_t") {
        inner_loader<computer_t>(node, entity_id);
    } else {
        throw std::runtime_error(std::string("Unknown component type to load: ") + xml_identity);
    }
}