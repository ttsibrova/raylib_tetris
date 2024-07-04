#pragma once
#include <vector>
#include <filesystem>

class HighScores
{
public:

    HighScores();

    struct ScoreRecord
    {
        size_t score;
        size_t lines;
        bool isNew;
    };

    void AddNewScore (size_t score, size_t lines);
    void AddSavedScore (size_t score, size_t lines);
    void AddSavedScore (ScoreRecord&& record);

    const std::vector<ScoreRecord>& GetRecords() const { return m_records; }

private:
    std::vector <ScoreRecord> m_records;
};

class HighScoresSavReader
{
public:
    bool Read (std::filesystem::path path, HighScores& target);
};

class HighScoresSavWriter
{
public:
    bool Write (const HighScores& source, std::filesystem::path folderPath, const std::wstring& filename);
};


