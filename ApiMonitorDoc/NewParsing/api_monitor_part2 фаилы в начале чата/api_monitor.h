#pragma once

#include <stdint.h>

// Qt (учитываю твой build с -qtnamespace QT)
#include <QTCore/QString>
#include <QTCore/QHash>
#include <QTCore/QSet>
#include <QTCore/QVector>

namespace apimon
{
    /// \brief
    /// Настройки импорта ApiMonitorDoc.
    struct Settings
    {
        QT::QString apiMonitorRootDir;   ///< Корневая папка ApiMonitorDoc (где Windows/ и Headers/).
        QT::QString outputDir;           ///< Папка, куда складываем логи (и позже кеш).
        QT::QString idaPluginsDir;       ///< Папка плагинов IDA (позже сюда положим бинарный кеш).
    };

    /// \brief
    /// Результаты Pass A: имена модулей/API/типов + includes.
    struct PassAResult
    {
        QT::QSet<QT::QString> modulesLower;                               ///< Найденные модули (lower-case).
        QT::QHash<QT::QString, QT::QSet<QT::QString>> apisByModule;       ///< ModuleLower -> set(apiName).
        QT::QHash<QT::QString, QT::QSet<QT::QString>> typesByModule;      ///< ModuleLower -> set(typeName).

        QT::QSet<QT::QString> includedFilesAbs;                           ///< Уникальные include-файлы (absolute paths).
        uint32_t includesTotalRefs = 0;                                   ///< Кол-во <Include ...> (с повторами).
        uint32_t includesUnique = 0;                                      ///< Кол-во уникальных include-файлов.
        uint32_t includesMissingFiles = 0;                                ///< Кол-во include на отсутствующие файлы.
        QT::QVector<QT::QString> missingIncludeSamples;                   ///< Сэмплы отсутствующих include (макс 50).

        uint32_t filesProcessed = 0;                                      ///< Кол-во обработанных XML файлов.
        uint32_t filesWithErrors = 0;                                     ///< Кол-во файлов с XML-ошибками.
    };

    bool BuildPassA(const Settings& s, PassAResult& out);
    bool WritePassALog(const Settings& s, const PassAResult& r);

    /// \brief
    /// Классификация сущности <Variable ...> по виду типа.
    enum class TypeKind : uint8_t
    {
        Unknown = 0,   ///< Вид не определён (или не поддержан на этом шаге).
        Alias,         ///< Type="Alias".
        Pointer,       ///< Type="Pointer".
        Array,         ///< Type="Array".
        Struct,        ///< Type="Struct".
        Union,         ///< Type="Union".
        Enum,          ///< <Enum> внутри Variable.
        Flags,         ///< <Flag> внутри Variable.
        Count          ///< Кол-во элементов enum (служебное значение, держим последним).
    };

    /// \brief
    /// Запись о типе из XML (<Variable ...>).
    struct TypeRecord
    {
        QT::QString moduleLower;   ///< Модуль-владелец (lower-case), например "ntdll.dll".
        QT::QString name;          ///< Имя типа/алиаса, атрибут Variable@Name.
        TypeKind kind = TypeKind::Unknown; ///< Вид типа.
        QT::QString base;          ///< Variable@Base (если задано).
        QT::QString count;         ///< Variable@Count (если задано), может быть "32" или "PointerCount".
    };

    /// \brief
    /// Результаты Pass B-1: список TypeRecord + агрегированная статистика.
    struct PassB1Result
    {
        QT::QVector<TypeRecord> types;                            ///< Все найденные Variable-записи.
        uint32_t filesProcessed = 0;                              ///< Кол-во обработанных XML файлов.
        uint32_t filesWithErrors = 0;                             ///< Кол-во файлов с XML-ошибками.
        uint32_t kindCounts[(uint32_t)TypeKind::Count] = { 0 };   ///< Счётчик по видам типов.
    };

    bool BuildPassB1(const Settings& s, PassB1Result& out);
    bool WritePassB1Log(const Settings& s, const PassB1Result& r);

} // namespace apimon