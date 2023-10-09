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
		inline static struct
		{
			std::string phone_number;
			std::string address;
			std::string full_name;
			int v;
		} contract{};
		inline static ServiceArea service_area;
		inline static ConnectionQueue connection_queue;
	 public:
        static const char *getMenuName() {
            return "Реєстрація клієнта";
        }

        static void render() {
			ImGui::PushStyleVar(ImGuiStyleVar_FrameBorderSize, 1);
			ImGui::InputText("Адреса", &contract.address);
			if(service_area.isAddressAvailable(contract.address)){
				ImGui::TextColored({0.0, 0.5, 0.0, 1}, "\tАдреса обслуговується");
			}else{
				ImGui::TextColored({0.9,0.1,0.1,1}, "\tАдреса не обслуговується");
			}
			if (ImGui::InputInt("Об'єм труби", &contract.v))
				service_area.setV(contract.v);
			if (service_area.supportV(contract.v)){
				ImGui::TextColored({0.0, 0.5, 0.0, 1}, "\tОб'єм доступний");
			}else{
				ImGui::TextColored({0.9,0.1,0.1,1}, "\tОб'єм не доступний");
			}
			ImGui::Text("%s", connection_queue.getAvaliableDate().c_str());
			ImGui::Text("Приблизна вартість підключення: %d грн", service_area.getPrice());
			ImGui::InputText("ПІБ", &contract.full_name);
			ImGui::InputText("Номер телефону", &contract.phone_number);
			if (ImGui::Button("Зареєструвати контракт", {0, 25})) {
				if (!service_area.isAddressAvailable(contract.address) || !service_area.supportV(contract.v) || contract.full_name.empty())
					ImGui::OpenPopup("Помилка рееєстрації контракту");
				else
				{
					connection_queue.addContract();
					ZeroMemory(&contract, sizeof(contract));
				}
			}
			if (ImGui::BeginPopupModal("Помилка рееєстрації контракту", nullptr, ImGuiWindowFlags_AlwaysAutoResize)) {
				if(!service_area.isAddressAvailable(contract.address))
					ImGui::Text("Не можливо зареєструвати контракт для цієї адреси");
				if(!service_area.supportV(contract.v))
					ImGui::Text("Вказаний об'єм не доступний за цією адресою");
				if(contract.full_name.empty())
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
