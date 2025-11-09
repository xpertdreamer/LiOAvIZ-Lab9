# LiOAvIZ-Lab9
## Build with CLion

# Console Interface Integration Guide

<div align="center">

**Language / Язык:**
[English](#english) | [Русский](#русский)

</div>

---

## English

### Quick Integration

#### 1. Basic Setup
Include the header and initialize in your `main.cpp`:

```cpp
#include "adapters/console_adapter.h"

int main() {
    try {
        // With custom config paths
        GraphConsoleAdapter adapter("config/console.conf", "config/aliases.conf");
    
        // Or with auto-detected configs
        // GraphConsoleAdapter adapter;

        adapter.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch(...) {
        std::cerr << "Unknown exception" << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
```

#### 2. Adding Your Commands
Extend the adapter class to add your own commands:

```cpp
class MyConsoleAdapter : public GraphConsoleAdapter {
public:
    MyConsoleAdapter(const std::string& config_path = "", const std::string& aliases_path = "")
        : GraphConsoleAdapter(config_path, aliases_path) {
        register_my_commands();
    }

private:
    void register_my_commands() {
        // Register your custom commands here
        console.register_command("mycommand",
            [this](const std::vector<std::string>& args) { this->cmd_mycommand(args); },
            "Description of my command",
            {"param1", "param2"},
            "mycommand <param1> <param2>"
        );
        
        // Add more commands as needed
        console.register_command("stats",
            [this](const std::vector<std::string>& args) { this->cmd_stats(args); },
            "Show application statistics"
        );
    }

    void cmd_mycommand(const std::vector<std::string>& args) {
        // Your command implementation
        std::cout << "Executing mycommand with args: ";
        for (const auto& arg : args) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    }
    
    void cmd_stats(const std::vector<std::string>& args) {
        // Your statistics implementation
        std::cout << "Application statistics..." << std::endl;
    }
};
```

### Core Features

#### Command System
- **Command Registration**: Easy registration with description, parameters, and usage
- **Parameter Handling**: Automatic parameter parsing and validation
- **Aliases Support**: Create shortcuts for frequently used commands
- **Built-in Commands**: `help`, `clear`, `history`, `exit` included by default

#### Configuration
```cpp
// Programmatic configuration
ConsoleConfig config;
config.prompt = "app> ";
config.history_size = 200;
config.colors_enabled = true;
console.set_config(config);

// Or load from file
console.load_config("path/to/config.conf");
```

#### History Management
- Configurable history size
- Access via `history` command
- Persistent between sessions (with custom implementation)

#### Color System
```cpp
// Use colored output
std::cout << console.get_color("success") << "Operation completed!" 
          << console.reset_color() << std::endl;

// Available colors: error, success, warning, info
// Custom colors via configuration
```

#### Error Handling
- Built-in exception handling for commands
- Custom error messages
- Help display on unknown commands

### Configuration Files

**config/console.conf**:
```ini
prompt = "myapp> "
welcome_msg = "My Application Console"
exit_msg = "Goodbye!"
unknown_msg = "Unknown command"
clear_screen_on_start = true
history_size = 100
press_to_exit = true
enable_colors = true
error_color = red
success_color = green
warning_color = yellow
info_color = blue
```

**config/aliases.conf**:
```ini
h = help
st = stats
mc = mycommand
```

### Advanced Usage

#### Custom Command Handlers
```cpp
console.register_command("advanced",
    [this](const std::vector<std::string>& args) {
        try {
            // Complex command logic
            if (args.size() < 2) {
                std::cout << "Error: Not enough arguments" << std::endl;
                return;
            }
            // Your implementation
        } catch (const std::exception& e) {
            std::cout << "Command failed: " << e.what() << std::endl;
        }
    },
    "Advanced command with validation",
    {"required", "optional"},
    "advanced <required> [optional]"
);
```

#### Building with CMake
```cmake
target_link_libraries(your_app PRIVATE console_library)
target_include_directories(your_app PRIVATE ${CMAKE_SOURCE_DIR}/include)
```

### Key Classes
- `Console` - Core console functionality
- `GraphConsoleAdapter` - Base adapter class (extend this)
- `ConfigLoader` - Configuration management
- `ConsoleConfig` - Console settings structure
- `CommandConfig` - Individual command configuration

---

## Русский

### Быстрая интеграция

#### 1. Базовая настройка
Подключите заголовок и инициализируйте в `main.cpp`:

```cpp
#include "adapters/console_adapter.h"

int main() {
    try {
        // С указанием путей к конфигурации
        GraphConsoleAdapter adapter("config/console.conf", "config/aliases.conf");
    
        // Или с автоматическим поиском конфигов
        // GraphConsoleAdapter adapter;

        adapter.run();
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return EXIT_FAILURE;
    } catch(...) {
        std::cerr << "Unknown exception" << std::endl;
        return EXIT_FAILURE;
    }
    return 0;
}
```

#### 2. Добавление своих команд
Расширьте класс адаптера для добавления собственных команд:

```cpp
class MyConsoleAdapter : public GraphConsoleAdapter {
public:
    MyConsoleAdapter(const std::string& config_path = "", const std::string& aliases_path = "")
        : GraphConsoleAdapter(config_path, aliases_path) {
        register_my_commands();
    }

private:
    void register_my_commands() {
        // Зарегистрируйте свои команды здесь
        console.register_command("моякоманда",
            [this](const std::vector<std::string>& args) { this->cmd_mycommand(args); },
            "Описание моей команды",
            {"параметр1", "параметр2"},
            "моякоманда <параметр1> <параметр2>"
        );
        
        // Добавьте дополнительные команды по необходимости
        console.register_command("статистика",
            [this](const std::vector<std::string>& args) { this->cmd_stats(args); },
            "Показать статистику приложения"
        );
    }

    void cmd_mycommand(const std::vector<std::string>& args) {
        // Реализация вашей команды
        std::cout << "Выполнение моей команды с аргументами: ";
        for (const auto& arg : args) {
            std::cout << arg << " ";
        }
        std::cout << std::endl;
    }
    
    void cmd_stats(const std::vector<std::string>& args) {
        // Реализация статистики
        std::cout << "Статистика приложения..." << std::endl;
    }
};
```

### Основные возможности

#### Система команд
- **Регистрация команд**: Простая регистрация с описанием, параметрами и использованием
- **Обработка параметров**: Автоматический разбор и валидация параметров
- **Поддержка псевдонимов**: Создание сокращений для часто используемых команд
- **Встроенные команды**: `help`, `clear`, `history`, `exit` включены по умолчанию

#### Конфигурация
```cpp
// Программная конфигурация
ConsoleConfig config;
config.prompt = "app> ";
config.history_size = 200;
config.colors_enabled = true;
console.set_config(config);

// Или загрузка из файла
console.load_config("path/to/config.conf");
```

#### Управление историей
- Настраиваемый размер истории
- Доступ через команду `history`
- Сохранение между сеансами (с пользовательской реализацией)

#### Система цветов
```cpp
// Использование цветного вывода
std::cout << console.get_color("success") << "Операция завершена!" 
          << console.reset_color() << std::endl;

// Доступные цвета: error, success, warning, info
// Пользовательские цвета через конфигурацию
```

#### Обработка ошибок
- Встроенная обработка исключений для команд
- Пользовательские сообщения об ошибках
- Показ справки при неизвестных командах

### Конфигурационные файлы

**config/console.conf**:
```ini
prompt = "myapp> "
welcome_msg = "My Application Console"
exit_msg = "Goodbye!"
unknown_msg = "Unknown command"
clear_screen_on_start = true
history_size = 100
press_to_exit = true
enable_colors = true
error_color = red
success_color = green
warning_color = yellow
info_color = blue
```

**config/aliases.conf**:
```ini
с = help
ст = статистика
мк = моякоманда
```

### Продвинутое использование

#### Пользовательские обработчики команд
```cpp
console.register_command("сложная",
    [this](const std::vector<std::string>& args) {
        try {
            // Сложная логика команды
            if (args.size() < 2) {
                std::cout << "Ошибка: Недостаточно аргументов" << std::endl;
                return;
            }
            // Ваша реализация
        } catch (const std::exception& e) {
            std::cout << "Ошибка команды: " << e.what() << std::endl;
        }
    },
    "Сложная команда с валидацией",
    {"обязательный", "опциональный"},
    "сложная <обязательный> [опциональный]"
);
```

#### Сборка с CMake
```cmake
target_link_libraries(your_app PRIVATE console_library)
target_include_directories(your_app PRIVATE ${CMAKE_SOURCE_DIR}/include)
```

### Основные классы
- `Console` - Основная функциональность консоли
- `GraphConsoleAdapter` - Базовый класс адаптера (расширяйте этот)
- `ConfigLoader` - Управление конфигурацией
- `ConsoleConfig` - Структура настроек консоли
- `CommandConfig` - Конфигурация отдельных команд

---

<div align="center">

*Last updated / Последнее обновление: 2025*

</div>
