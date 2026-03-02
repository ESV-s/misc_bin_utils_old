#pragma once

#include <stdint.h>

// Qt headers are in <QtCore/...>, even when namespace is QT::
#include <QtCore/QString>
#include <QtCore/QHash>
#include <QtCore/QSet>
#include <QtCore/QVector>

namespace apimon
{
    /// \brief
    /// Настройки импорта ApiMonitorDoc.
    struct Settings
    {
        QT::QString apiMonitorRootDir;   ///< Корневая папка ApiMonitorDoc (где Windows/ и Headers/).
        QT::QString outputDir;           ///< Папка, куда складываем логи.
        QT::QString idaPluginsDir;       ///< Папка плагинов IDA (сюда положим бинарный кеш).
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
        Interface,     ///< Type="Interface" (COM-интерфейсы и похожие абстрактные типы).
        Enum,          ///< <Enum> внутри Variable.
        Flags,         ///< <Flag> внутри Variable.
        Count          ///< Кол-во элементов enum (служебное значение, держим последним).
    };

    /// \brief
    /// Поле структуры/объединения из XML (<Field .../>).
    struct FieldRecord
    {
        QT::QString type;     ///< Field@Type (как в XML).
        QT::QString name;     ///< Field@Name.
        QT::QString display;  ///< Field@Display (если задано).
        QT::QString count;    ///< Field@Count (если задано; может быть выражением/константой).
    };

    /// \brief
    /// Запись о типе из XML (<Variable ...>).
    struct TypeRecord
    {
        QT::QString moduleLower;   ///< Модуль-владелец (lower-case), например "ntdll.dll".
        QT::QString name;          ///< Имя типа/алиаса, атрибут Variable@Name.
        QT::QString typeAttr;      ///< Исходная строка атрибута Variable@Type (trimmed).
        TypeKind kind = TypeKind::Unknown; ///< Вид типа.
        QT::QString base;          ///< Variable@Base (если задано).
        QT::QString count;         ///< Variable@Count (если задано), может быть "32" или "PointerCount".

        QT::QVector<FieldRecord> fields; ///< Поля для Struct/Union (оставлено под будущее).
    };

    /// \brief
    /// Результаты Pass B-1: список TypeRecord + агрегированная статистика.
    struct PassB1Result
    {
        QT::QVector<TypeRecord> types;                            ///< Все найденные Variable-записи.
        uint32_t filesProcessed = 0;                              ///< Кол-во обработанных XML файлов.
        uint32_t filesWithErrors = 0;                             ///< Кол-во файлов с XML-ошибками.
        uint32_t kindCounts[(uint32_t)TypeKind::Count] = { 0 };   ///< Счётчик по видам типов.
        QT::QHash<QT::QString, uint32_t> unknownTypeAttrCounts;   ///< Unknown Variable@Type (key=lower-case Type).
        QT::QHash<QT::QString, QT::QString> unknownTypeAttrOriginal; ///< Первое встреченное написание unknown Type.
    };

    bool BuildPassB1(const Settings& s, PassB1Result& out);
    bool WritePassB1Log(const Settings& s, const PassB1Result& r);

    /// \brief
    /// Результаты Pass B-2: статистика по полям Struct/Union.
    struct PassB2Result
    {
        uint32_t filesProcessed = 0;   ///< Кол-во обработанных XML файлов.
        uint32_t filesWithErrors = 0;  ///< Кол-во файлов с XML-ошибками.

        uint32_t structTypes = 0;      ///< Кол-во Variable Type="Struct".
        uint32_t unionTypes = 0;       ///< Кол-во Variable Type="Union".

        uint64_t fieldsTotal = 0;      ///< Всего Field-элементов внутри Struct/Union.
        uint64_t fieldsWithDisplay = 0;///< Сколько полей имеют атрибут Display.
        uint64_t fieldsWithCount = 0;  ///< Сколько полей имеют атрибут Count.

        QT::QHash<QT::QString, uint32_t> fieldTypeCounts;         ///< Частоты Field@Type (key=lower-case type, value=count).
        QT::QHash<QT::QString, QT::QString> fieldTypeOriginal;    ///< Первое написание Field@Type (key=lower-case type, value=original).

        QT::QVector<QT::QString> fieldSamples; ///< Сэмплы строк (макс 60) для проверки глазами.
    };

    bool BuildPassB2(const Settings& s, PassB2Result& out);
    bool WritePassB2Log(const Settings& s, const PassB2Result& r);

    // --------------------------------------------------------------------
    // Pass SIG-1: сигнатура входных XML (контроль "XML не менялись?")
    // --------------------------------------------------------------------

    /// \brief
    /// Сигнатура одного XML файла.
    struct InputFileSignature
    {
        QT::QString relPath;     ///< Путь относительно Settings::apiMonitorRootDir (нормализован '/').
        int64_t sizeBytes = 0;   ///< Размер файла в байтах.
        int64_t mtimeUtcMs = 0;  ///< Время модификации файла в UTC (msecs since epoch).
        QT::QString sha1Hex;     ///< SHA1 содержимого файла в hex.
    };

    /// \brief
    /// Результат подсчёта сигнатуры набора входных XML.
    struct InputSignatureResult
    {
        uint32_t filesProcessed = 0;    ///< Сколько *.xml файлов найдено и обработано.
        uint32_t filesWithErrors = 0;   ///< Сколько *.xml файлов не удалось прочитать/захэшировать.
        int64_t totalBytes = 0;         ///< Суммарный размер всех XML (байт).
        QT::QString combinedSha1Hex;    ///< Итоговый SHA1 по всему набору (путь+size+mtime+sha1 каждого файла).
        QT::QVector<InputFileSignature> files; ///< Пер-файловые записи (для диагностики).
    };

    bool BuildInputSignature(const Settings& s, InputSignatureResult& out);
    bool WriteInputSignatureLog(const Settings& s, const InputSignatureResult& r);

    // --------------------------------------------------------------------
    // Cache BIN-0: минимальный бинарник-кеш (пока только заголовок + SHA1)
    // --------------------------------------------------------------------

    /// \brief
    /// Заголовок кеш-бинарника (header-only).
    struct CacheHeader
    {
        uint32_t magic = 0;              ///< Магия формата (APMC).
        uint32_t version = 0;            ///< Версия формата заголовка.
        uint32_t headerSize = 0;         ///< Размер заголовка в байтах (для совместимости).
        uint32_t filesProcessed = 0;     ///< Количество XML файлов при построении кеша.
        int64_t totalBytes = 0;          ///< Суммарный размер XML (байт) при построении кеша.
        uint8_t combinedSha1[20];        ///< CombinedSHA1 входных XML (20 байт).
        int64_t createdUtcMs = 0;        ///< Когда создан кеш (UTC msecs since epoch).
        uint32_t reserved0 = 0;          ///< Резерв под будущее.
        uint32_t reserved1 = 0;          ///< Резерв под будущее.
    };

    /// \brief
    /// Путь к кеш-бинарнику рядом с плагином (idaPluginsDir\apimon_cache.bin).
    QT::QString GetCacheBinPath(const Settings& s);

    bool BuildCacheHeaderFromSignature(const InputSignatureResult& sig, CacheHeader& out);
    bool WriteCacheHeaderBin(const Settings& s, const CacheHeader& ch);
    bool ReadCacheHeaderBin(const Settings& s, CacheHeader& out);
    bool IsCacheHeaderValidForSignature(const CacheHeader& ch, const InputSignatureResult& sig);

} // namespace apimon