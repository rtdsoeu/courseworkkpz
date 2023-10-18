#pragma once
#ifndef COURSEWORK_REGISTER_CLIENT_HPP
#define COURSEWORK_REGISTER_CLIENT_HPP

#include "../imwindows/imwindows.hpp"
#include "../plumbing/person.hpp"
#include "../imgui/misc/cpp/imgui_stdlib.h"
#include "../plumbing/service_area.hpp"
#include "../plumbing/connection_queue.hpp"

namespace Requests {
    class RegisterClient {
		Contract input_contract;
		ServiceArea service_area;
		ConnectionQueue connection_queue;
	 public:
        auto getMenuName() {
            return "Реєстрація клієнта";
        }

        void render() {
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
			ImGui::InputText("Адреса", &input_contract.address);
			if(service_area.isAddressAvailable(input_contract.address)){
				ImGui::TextColored({0.0, 0.5, 0.0, 1.0}, "\tАдреса обслуговується");
			}else{
				ImGui::TextColored({0.9, 0.1, 0.1, 1.0}, "\tАдреса не обслуговується");
			}
			if (ImGui::InputInt("Об'єм труби", &input_contract.volume))
				service_area.setV(input_contract.volume);
			if (service_area.supportV(input_contract.volume)){
				ImGui::TextColored({0.0, 0.5, 0.0, 1.0}, "\tОб'єм доступний");
			}else{
				ImGui::TextColored({0.9, 0.1, 0.1, 1.0}, "\tОб'єм не доступний");
			}
			ImGui::Text("%s", connection_queue.getAvaliableDate().c_str());
			ImGui::Text("Приблизна вартість підключення: %d грн", service_area.getPrice());
			ImGui::InputText("ПІБ", &input_contract.full_name);
			ImGui::InputText("Номер телефону", &input_contract.phone_number);
			if (ImGui::Button("Зареєструвати контракт", {0, 25})) {
				if (!service_area.isAddressAvailable(input_contract.address) || 
					!service_area.supportV(input_contract.volume) || 
					input_contract.full_name.empty())
					ImGui::OpenPopup("Помилка рееєстрації контракту");
				else
				{
					connection_queue.addContract(input_contract);
					ZeroMemory(&input_contract, sizeof(input_contract));
				}
			}
			if (ImGui::BeginPopupModal("Помилка рееєстрації контракту", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
				if(!service_area.isAddressAvailable(input_contract.address))
					ImGui::Text("Не можливо зареєструвати контракт для цієї адреси");
				if(!service_area.supportV(input_contract.volume))
					ImGui::Text("Вказаний об'єм не доступний за цією адресою");
				if(input_contract.full_name.empty())
					ImGui::Text("Не вказано ПІБ клієнта");
				if (ImGui::Button("Закрити##input", {-1, 0}))
					ImGui::CloseCurrentPopup();
				ImGui::EndPopup();
			}
			ImGui::PopStyleVar(1);
        }
    };
}

#endif //COURSEWORK_REGISTER_CLIENT_HPP
