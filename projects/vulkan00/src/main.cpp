#include <iostream>
#include <vulkan/vulkan.h>

int main()
{
    // Initialisation de la bibliothèque Vulkan
    VkInstance instance;

    // Spécifier les informations d'application
    VkApplicationInfo appInfo = {};
    appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
    appInfo.pApplicationName = "Hello Vulkan";
    appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.pEngineName = "No Engine";
    appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
    appInfo.apiVersion = VK_API_VERSION_1_0;

    // Créer une instance Vulkan
    VkInstanceCreateInfo createInfo = {};
    createInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
    createInfo.pApplicationInfo = &appInfo;

    // Créer l'instance Vulkan
    if (vkCreateInstance(&createInfo, nullptr, &instance) != VK_SUCCESS) {
        std::cerr << "Erreur : impossible de créer une instance Vulkan !" << std::endl;
        return -1;
    }

    std::cout << "Vulkan initialisé avec succès !" << std::endl;

    // Nettoyer l'instance Vulkan
    vkDestroyInstance(instance, nullptr);

    return 0;
}
