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
        QT::QString idaPluginsDir;       ///< Папка plugins/ (рядом будут bin кеши).
    };

    // --------------------------------------------------------------------
    // Общие утилиты (пути, сбор *.xml)
    // --------------------------------------------------------------------

    /// \brief
    /// Нормализация имени модуля для ключей: lower-case + trim + ".dll" (если надо).
    QT::QString NormalizeModuleNameLower(const QT::QString& moduleName);

    /// \brief
    /// Собирает список *.xml файлов рекурсивно.
    bool CollectXmlFilesRecursive(const QT::QString& rootDir, QT::QVector<QT::QString>& outFiles);

    // --------------------------------------------------------------------
    // Pass A-1: базовая статистика файлов + проверка читабельности
    // --------------------------------------------------------------------

    struct PassAResult
    {
        uint32_t filesProcessed = 0; ///< Сколько *.xml файлов найдено и прочитано.
        uint32_t filesWithErrors = 0; ///< Сколько *.xml файлов не удалось открыть/прочитать.
        int64_t totalBytes = 0; ///< Суммарный размер обработанных файлов (байт).
    };

    bool BuildPassA(const Settings& s, PassAResult& out);
    bool WritePassALog(const Settings& s, const PassAResult& r);

    // --------------------------------------------------------------------
    // Pass B-1: разбор <Variable ...> (типы/алиасы/структуры/enum/flags)
    // --------------------------------------------------------------------

    /// \brief
    /// Тип сущности (по Variable@Type + наличию <Enum>/<Flag>).
    enum class TypeKind : uint32_t
    {
        Unknown = 0,
        Alias = 1,
        Pointer = 2,
        Array = 3,
        Struct = 4,
        Union_ = 5,
        Enum = 6,
        Flags = 7,
        Interface_ = 8,
        FunctionPointer = 9,
    };

    /// \brief
    /// Поле структуры/union из <Field .../>.
    struct FieldRecord
    {
        QT::QString type;    ///< Type поля (атрибут @Type).
        QT::QString name;    ///< Name поля (атрибут @Name).
        QT::QString display; ///< Display (если задано).
        QT::QString count;   ///< Count (если задано).
    };

    /// \brief
    /// Элемент перечисления/флагов (внутри <Enum> или <Flag>).
    struct EnumValueRecord
    {
        QT::QString name;     ///< Name элемента перечисления/флага (атрибут @Name).
        QT::QString value;    ///< Value элемента перечисления/флага (атрибут @Value), может быть выражением.
        QT::QString display;  ///< Display (если задано).
    };

    /// \brief
    /// Запись типа из <Variable ...>.
    struct TypeRecord
    {
        QT::QString moduleLower; ///< Модуль (dll) в lower-case, из <Module Name="...">.
        QT::QString name;        ///< Variable@Name
        QT::QString typeAttr;    ///< Variable@Type (как строка, для диагностики)
        QT::QString base;        ///< Variable@Base
        QT::QString count;       ///< Variable@Count (для Array)
        TypeKind kind = TypeKind::Unknown; ///< Классификация по TypeAttr + <Enum>/<Flag>.

        QT::QVector<EnumValueRecord> enumValues; ///< Значения для Enum/Flags (если найдены в XML).
        QT::QVector<FieldRecord> fields; ///< Поля для Struct/Union.
    };

    /// \brief
    /// Результат Pass B-1.
    struct PassB1Result
    {
        uint32_t filesProcessed = 0; ///< Сколько *.xml файлов обработано.
        uint32_t filesWithErrors = 0; ///< Сколько файлов дали ошибки чтения/парсинга.
        QT::QVector<TypeRecord> types; ///< Сохранённые записи Variable.
        QT::QHash<uint32_t, uint32_t> kindCounts; ///< TypeKind -> count
        QT::QHash<QT::QString, uint32_t> unknownTypeAttrCounts; ///< typeAttrLower -> count
        QT::QHash<QT::QString, QT::QString> unknownTypeAttrOriginal; ///< typeAttrLower -> original casing
    };

    bool BuildPassB1(const Settings& s, PassB1Result& out);
    bool WritePassB1Log(const Settings& s, const PassB1Result& r);

    // --------------------------------------------------------------------
    // Pass B-2: расширенная статистика (пока без хранения новых сущностей)
    // --------------------------------------------------------------------

    struct PassB2Result
    {
        uint32_t filesProcessed = 0; ///< Сколько *.xml файлов обработано.
        uint32_t filesWithErrors = 0; ///< Сколько файлов дали ошибки чтения/парсинга.
        uint32_t structFieldsTotal = 0; ///< Сколько всего <Field ...> встречено (для всех struct/union).
    };

    bool BuildPassB2(const Settings& s, PassB2Result& out);
    bool WritePassB2Log(const Settings& s, const PassB2Result& r);

    // --------------------------------------------------------------------
    // Pass F-1: функции <Api ...> (имя, параметры, return)
    // --------------------------------------------------------------------

    /// \brief
    /// Описание параметра функции из блока <Api ...>.
    struct ApiParamRecord
    {
        QT::QString name;     ///< Имя параметра (атрибут @Name).
        QT::QString type;     ///< Тип параметра (атрибут @Type), как строка из XML.
        QT::QString display;  ///< Display (если задан).
        QT::QString count;    ///< Count (если задан).
        QT::QString dir;      ///< Dir/Direction (если задано).
    };

    /// \brief
    /// Описание API-функции из XML (<Api ...>).
    struct ApiFunctionRecord
    {
        QT::QString moduleLower; ///< Модуль (dll) в lower-case.
        QT::QString name;        ///< Имя функции.
        QT::QString dll;         ///< Явный Dll/Library (если задано в XML).
        QT::QString convention;  ///< Calling convention (если задано).
        QT::QString retType;     ///< Return type (строка из XML).
        QT::QVector<ApiParamRecord> params; ///< Параметры.
        QT::QString links;       ///< Доп. поле: ссылки/описания (пока заглушка, пустая строка).
    };

    /// \brief
    /// Результат прохода Pass F-1.
    struct PassF1Result
    {
        uint32_t filesProcessed = 0; ///< Сколько *.xml файлов обработано.
        uint32_t filesWithErrors = 0; ///< Сколько файлов дали ошибки чтения/парсинга.
        uint32_t apisTotal = 0;       ///< Сколько <Api ...> встретилось всего.
        uint32_t paramsTotal = 0;     ///< Сколько параметров суммарно встретилось.
        QT::QVector<ApiFunctionRecord> apis; ///< Сохранённые API записи.
        QT::QHash<QT::QString, uint32_t> apiNameCounts; ///< nameLower -> count (для статистики).
    };

    /// \brief
    /// Построить список API-функций (Pass F-1).
    bool BuildPassF1(const Settings& s, PassF1Result& out);

    /// \brief
    /// Записать лог Pass F-1 (для диагностики).
    bool WritePassF1Log(const Settings& s, const PassF1Result& r);

    // --------------------------------------------------------------------
    // Pass SIG-1: сигнатура входных XML (чтобы решать, пересобирать ли кеш)
    // --------------------------------------------------------------------

    /// \brief
    /// Подпись одного XML файла (для комбинированного хэша).
    struct InputFileSignature
    {
        QT::QString relPath; ///< Путь относительно apiMonitorRootDir.
        int64_t size = 0;    ///< Размер (байт).
        int64_t mtime = 0;   ///< mtime (secs since epoch).
        uint8_t sha1[20];    ///< SHA1 содержимого файла.
    };

    /// \brief
    /// Итоговая сигнатура всего набора XML.
    struct InputSignatureResult
    {
        uint32_t filesProcessed = 0; ///< Сколько *.xml файлов найдено и обработано.
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

    /// \brief
    /// Построить заголовок кеша по InputSignatureResult.
    bool BuildCacheHeaderFromSignature(const InputSignatureResult& sig, CacheHeader& out);

    /// \brief
    /// Проверить, соответствует ли заголовок кеша текущей сигнатуре XML.
    bool IsCacheHeaderValidForSignature(const CacheHeader& ch, const InputSignatureResult& sig);

    /// \brief
    /// Записать кеш-заголовок (apimon_cache.bin).
    bool WriteCacheHeaderBin(const Settings& s, const CacheHeader& ch);

    /// \brief
    /// Прочитать кеш-заголовок (apimon_cache.bin).
    bool ReadCacheHeaderBin(const Settings& s, CacheHeader& out);

    // --------------------------------------------------------------------
    // Data BIN-1: основной бинарник базы (типы + функции).
    // --------------------------------------------------------------------

    /// \brief
    /// Структура in-memory базы, загруженной из apimon_data.bin.
    /// (Это то, чем будет пользоваться плагин для подсказок/применения типов.)
    struct DataBinDb
    {
        QT::QString combinedSha1Hex;            ///< Итоговый SHA1 входных XML, с которым собрана база.
        QT::QVector<TypeRecord> types;          ///< Типы/структуры/enum/flags и т.д.
        QT::QVector<ApiFunctionRecord> apis;    ///< Функции (с параметрами/ret + links).
    };

    /// \brief
    /// Путь к файлу основной базы (рядом с плагином).
    QT::QString DataBinPath(const Settings& s);

    /// \brief
    /// Записать основную базу apimon_data.bin.
    /// \param s Настройки путей.
    /// \param sig Сигнатура входных XML (для проверки актуальности).
    /// \param b1 Результаты Pass B-1 (типы + поля/enumValues).
    /// \param f1 Результаты Pass F-1 (функции).
    bool WriteDataBin(const Settings& s, const InputSignatureResult& sig, const PassB1Result& b1, const PassF1Result& f1);

    /// \brief
    /// Прочитать основную базу apimon_data.bin.
    /// \param s Настройки путей.
    /// \param out Заполненная база.
    bool ReadDataBin(const Settings& s, DataBinDb& out);

} // namespace apimon