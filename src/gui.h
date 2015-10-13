// Copyright 2014 Toggl Desktop developers.

#ifndef SRC_GUI_H_
#define SRC_GUI_H_

#include <set>
#include <string>
#include <vector>

#include "./https_client.h"
#include "./proxy.h"
#include "./settings.h"
#include "./toggl_api.h"
#include "./toggl_api_private.h"
#include "./types.h"

namespace Poco {
class Logger;
}

namespace toggl {

namespace view {

class TimeEntry {
 public:
    TimeEntry()
        : DurationInSeconds(0)
    , Description("")
    , ProjectAndTaskLabel("")
    , TaskLabel("")
    , ProjectLabel("")
    , ClientLabel("")
    , WID(0)
    , PID(0)
    , TID(0)
    , Duration("")
    , Color("")
    , GUID("")
    , Billable(false)
    , Tags("")
    , Started(0)
    , Ended(0)
    , StartTimeString("")
    , EndTimeString("")
    , UpdatedAt(0)
    , DurOnly(false)
    , DateHeader("")
    , DateDuration("")
    , IsHeader(false)
    , CanAddProjects(false)
    , CanSeeBillable(false)
    , DefaultWID(0)
    , WorkspaceName("")
    , Error(noError) {}

    int64_t DurationInSeconds;
    std::string Description;
    std::string ProjectAndTaskLabel;
    std::string TaskLabel;
    std::string ProjectLabel;
    std::string ClientLabel;
    uint64_t WID;
    uint64_t PID;
    uint64_t TID;
    std::string Duration;
    std::string Color;
    std::string GUID;
    bool Billable;
    std::string Tags;
    uint64_t Started;
    uint64_t Ended;
    std::string StartTimeString;
    std::string EndTimeString;
    uint64_t UpdatedAt;
    bool DurOnly;
    // In case it's a header
    std::string DateHeader;
    std::string DateDuration;
    bool IsHeader;
    // Additional fields; only when in time entry editor
    bool CanAddProjects;
    bool CanSeeBillable;
    uint64_t DefaultWID;
    std::string WorkspaceName;
    // If syncing a time entry ended with an error,
    // the error is attached to the time entry
    std::string Error;

    bool operator == (const TimeEntry& other) const;
};

class Autocomplete {
 public:
    Autocomplete()
        : Text("")
    , Description("")
    , ProjectAndTaskLabel("")
    , TaskLabel("")
    , ProjectLabel("")
    , ClientLabel("")
    , ProjectColor("")
    , TaskID(0)
    , ProjectID(0)
    , WorkspaceID(0)
    , Type(0)
    , Tags("")
    , WorkspaceName("")
    , ClientID(0) {}

    bool IsTimeEntry() const {
        return kAutocompleteItemTE == Type;
    }
    bool IsTask() const {
        return kAutocompleteItemTask == Type;
    }
    bool IsProject() const {
        return kAutocompleteItemProject == Type;
    }
    bool IsWorkspace() const {
        return kAutocompleteItemWorkspace == Type;
    }

    std::string String() const {
        std::stringstream ss;
        ss << "AutocompleteItem"
           << " Text=" << Text
           << " Description=" << Description
           << " ProjectAndTaskLabel=" << ProjectAndTaskLabel
           << " TaskLabel=" << TaskLabel
           << " ProjectLabel=" << ProjectLabel
           << " ClientLabel=" << ClientLabel
           << " ProjectColor=" << ProjectColor
           << " TaskID=" << TaskID
           << " ProjectID=" << ProjectID
           << " WorkspaceID=" << WorkspaceID
           << " Type=" << Type
           << " WorkspaceName=" << WorkspaceName
           << " Tags=" << Tags;
        return ss.str();
    }

    // This is what is displayed to user, includes project and task.
    std::string Text;
    // This is copied to "time_entry.description" field if item is selected
    std::string Description;
    // Project label, if has a project
    std::string ProjectAndTaskLabel;
    std::string TaskLabel;
    std::string ProjectLabel;
    std::string ClientLabel;
    std::string ProjectColor;
    uint64_t TaskID;
    uint64_t ProjectID;
    uint64_t WorkspaceID;
    uint64_t Type;
    // If its a time entry, it has tags
    std::string Tags;
    std::string WorkspaceName;
    uint64_t ClientID;

    bool operator == (const Autocomplete& other) const;
};

class Generic {
 public:
    Generic()
        : ID(0)
    , WID(0)
    , GUID("")
    , Name("")
    , WorkspaceName("") {}

    uint64_t ID;
    uint64_t WID;
    std::string GUID;
    std::string Name;
    std::string WorkspaceName;

    bool operator == (const Generic& other) const;
};

class Settings {
 public:
    Settings()
        : UseProxy(false)
    , ProxyHost("")
    , ProxyPort(0)
    , ProxyUsername("")
    , ProxyPassword("")
    , UseIdleDetection(false)
    , MenubarTimer(false)
    , MenubarProject(false)
    , DockIcon(false)
    , OnTop(false)
    , Reminder(false)
    , RecordTimeline(false)
    , IdleMinutes(0)
    , FocusOnShortcut(false)
    , ReminderMinutes(0)
    , ManualMode(false)
    , AutodetectProxy(false)
    , RemindMon(false)
    , RemindTue(false)
    , RemindWed(false)
    , RemindThu(false)
    , RemindFri(false)
    , RemindSat(false)
    , RemindSun(false)
    , RemindStarts("")
    , RemindEnds("")
    , Autotrack(false)
    , OpenEditorOnShortcut(false) {}

    bool UseProxy;
    std::string ProxyHost;
    uint64_t ProxyPort;
    std::string ProxyUsername;
    std::string ProxyPassword;
    bool UseIdleDetection;
    bool MenubarTimer;
    bool MenubarProject;
    bool DockIcon;
    bool OnTop;
    bool Reminder;
    bool RecordTimeline;
    uint64_t IdleMinutes;
    bool FocusOnShortcut;
    uint64_t ReminderMinutes;
    bool ManualMode;
    bool AutodetectProxy;
    bool RemindMon;
    bool RemindTue;
    bool RemindWed;
    bool RemindThu;
    bool RemindFri;
    bool RemindSat;
    bool RemindSun;
    std::string RemindStarts;
    std::string RemindEnds;
    bool Autotrack;
    bool OpenEditorOnShortcut;

    bool operator == (const Settings& other) const;
};

class AutotrackerRule {
 public:
    AutotrackerRule()
        : ID(0)
    , Term("")
    , PID(0)
    , ProjectName("") {}

    int64_t ID;
    std::string Term;
    uint64_t PID;
    std::string ProjectName;

    bool operator == (const AutotrackerRule& other) const;
};

class TimelineEvent {
 public:
    TimelineEvent()
        : ID(0)
    , Title("")
    , Filename("")
    , StartTime(0)
    , EndTime(0)
    , Idle(false) {}

    int64_t ID;
    std::string Title;
    std::string Filename;
    uint64_t StartTime;
    uint64_t EndTime;
    bool Idle;

    bool operator == (const TimelineEvent& other) const;
};

}  // namespace view

class Client;
class Project;
class RelatedData;
class User;
class TimeEntry;
class Workspace;

class GUI : public SyncStateMonitor {
 public:
    GUI()
        : on_display_app_(nullptr)
    , on_display_error_(nullptr)
    , on_display_online_state_(nullptr)
    , on_display_login_(nullptr)
    , on_display_url_(nullptr)
    , on_display_reminder_(nullptr)
    , on_display_time_entry_list_(nullptr)
    , on_display_time_entry_autocomplete_(nullptr)
    , on_display_project_autocomplete_(nullptr)
    , on_display_workspace_select_(nullptr)
    , on_display_client_select_(nullptr)
    , on_display_tags_(nullptr)
    , on_display_time_entry_editor_(nullptr)
    , on_display_settings_(nullptr)
    , on_display_timer_state_(nullptr)
    , on_display_idle_notification_(nullptr)
    , on_display_mini_timer_autocomplete_(nullptr)
    , on_display_sync_state_(nullptr)
    , on_display_unsynced_items_(nullptr)
    , on_display_update_(nullptr)
    , on_display_update_download_state_(nullptr)
    , on_display_autotracker_rules_(nullptr)
    , on_display_autotracker_notification_(nullptr)
    , on_display_promotion_(nullptr)
    , lastSyncState(-1)
    , lastUnsyncedItemsCount(-1)
    , lastDisplayLoginOpen(false)
    , lastDisplayLoginUserID(0)
    , lastOnlineState(-1)
    , lastErr(noError) {}

    ~GUI() {}

    void DisplayApp();

    error DisplayError(const error);

    void DisplaySyncState(const Poco::Int64 state);

    void DisplayOnlineState(const Poco::Int64 state);

    void DisplayUnsyncedItems(const Poco::Int64 count);

    void DisplayReminder();

    void DisplayAutotrackerNotification(toggl::Project *p);

    void DisplayMinitimerAutocomplete(std::vector<toggl::view::Autocomplete> *);

    void DisplayTimeEntryAutocomplete(std::vector<toggl::view::Autocomplete> *);

    void DisplayProjectAutocomplete(std::vector<toggl::view::Autocomplete> *);

    void DisplayTimeEntryList(
        const bool open,
        const RelatedData &related,
        const std::vector<TimeEntry *> list);

    void DisplayWorkspaceSelect(std::vector<toggl::Workspace *> *list);

    void DisplayClientSelect(
        const RelatedData &,
        std::vector<toggl::Client *> *);

    void DisplayTags(std::vector<std::string> *tags);

    void DisplayAutotrackerRules(
        const RelatedData &related,
        const std::set<std::string> &autotracker_titles);

    void DisplayTimeEntryEditor(
        const bool open,
        const RelatedData &related,
        const TimeEntry *te,
        const std::string focused_field_name,
        const Poco::Int64 total_duration_for_date,
        const User *user);

    void DisplayURL(const std::string);

    void DisplayLogin(const bool open, const uint64_t user_id);

    void DisplaySettings(
        const bool open,
        const bool record_timeline,
        const Settings settings,
        const bool use_proxy,
        const Proxy proxy);

    void DisplayTimerState(
        const RelatedData &related,
        const TimeEntry *te,
        const Poco::Int64 total_duration_for_date);

    void DisplayIdleNotification(const std::string guid,
                                 const std::string since,
                                 const std::string duration,
                                 const uint64_t started,
                                 const std::string description);

    void DisplayUpdate(const std::string URL);

    void DisplayUpdateDownloadState(
        const std::string version,
        const Poco::Int64 download_state);

    error VerifyCallbacks();

    void OnDisplayUpdate(TogglDisplayUpdate cb) {
        on_display_update_ = cb;
    }

    void OnDisplayUpdateDownloadState(TogglDisplayUpdateDownloadState cb) {
        on_display_update_download_state_ = cb;
    }

    void OnDisplayApp(TogglDisplayApp cb) {
        on_display_app_ = cb;
    }

    void OnDisplayError(TogglDisplayError cb) {
        on_display_error_ = cb;
    }

    void OnDisplayOnlineState(TogglDisplayOnlineState cb) {
        on_display_online_state_ = cb;
    }

    void OnDisplayLogin(TogglDisplayLogin cb) {
        on_display_login_ = cb;
    }

    void OnDisplayURL(TogglDisplayURL cb) {
        on_display_url_ = cb;
    }

    void OnDisplayReminder(TogglDisplayReminder cb) {
        on_display_reminder_ = cb;
    }

    void OnDisplayAutotrackerNotification(
        TogglDisplayAutotrackerNotification cb) {
        on_display_autotracker_notification_ = cb;
    }

    void OnDisplayTimeEntryList(TogglDisplayTimeEntryList cb) {
        on_display_time_entry_list_ = cb;
    }

    void OnDisplayWorkspaceSelect(TogglDisplayViewItems cb) {
        on_display_workspace_select_ = cb;
    }

    void OnDisplayClientSelect(TogglDisplayViewItems cb) {
        on_display_client_select_ = cb;
    }

    void OnDisplayTags(TogglDisplayViewItems cb) {
        on_display_tags_ = cb;
    }

    void OnDisplayTimeEntryEditor(TogglDisplayTimeEntryEditor cb) {
        on_display_time_entry_editor_ = cb;
    }

    void OnDisplayTimeEntryAutocomplete(TogglDisplayAutocomplete cb) {
        on_display_time_entry_autocomplete_ = cb;
    }

    void OnDisplayProjectAutocomplete(TogglDisplayAutocomplete cb) {
        on_display_project_autocomplete_ = cb;
    }

    void OnDisplaySettings(TogglDisplaySettings cb) {
        on_display_settings_ = cb;
    }

    void OnDisplayTimerState(TogglDisplayTimerState cb) {
        on_display_timer_state_ = cb;
    }

    void OnDisplayIdleNotification(TogglDisplayIdleNotification cb) {
        on_display_idle_notification_  = cb;
    }

    void OnDisplayMinitimerAutocomplete(TogglDisplayAutocomplete cb) {
        on_display_mini_timer_autocomplete_ = cb;
    }

    void OnDisplaySyncState(TogglDisplaySyncState cb) {
        on_display_sync_state_ = cb;
    }

    void OnDisplayUnsyncedItems(TogglDisplayUnsyncedItems cb) {
        on_display_unsynced_items_ = cb;
    }

    void OnDisplayAutotrackerRules(TogglDisplayAutotrackerRules cb) {
        on_display_autotracker_rules_ = cb;
    }

    void OnDisplayPromotion(TogglDisplayPromotion cb) {
        on_display_promotion_ = cb;
    }

    bool CanDisplayUpdate() const {
        return !!on_display_update_;
    }

    bool CanDisplayUpdateDownloadState() const {
        return !!on_display_update_download_state_;
    }

    bool CanDisplayAutotrackerRules() const {
        return !!on_display_autotracker_rules_;
    }

    bool CanDisplayPromotion() const {
        return !!on_display_promotion_;
    }

    void DisplayPromotion(const int64_t promotion_type) {
        if (on_display_promotion_) {
            on_display_promotion_(promotion_type);
        }
    }

 private:
    error findMissingCallbacks();

    TogglDisplayApp on_display_app_;
    TogglDisplayError on_display_error_;
    TogglDisplayOnlineState on_display_online_state_;
    TogglDisplayLogin on_display_login_;
    TogglDisplayURL on_display_url_;
    TogglDisplayReminder on_display_reminder_;
    TogglDisplayTimeEntryList on_display_time_entry_list_;
    TogglDisplayAutocomplete on_display_time_entry_autocomplete_;
    TogglDisplayAutocomplete on_display_project_autocomplete_;
    TogglDisplayViewItems on_display_workspace_select_;
    TogglDisplayViewItems on_display_client_select_;
    TogglDisplayViewItems on_display_tags_;
    TogglDisplayTimeEntryEditor on_display_time_entry_editor_;
    TogglDisplaySettings on_display_settings_;
    TogglDisplayTimerState on_display_timer_state_;
    TogglDisplayIdleNotification on_display_idle_notification_;
    TogglDisplayAutocomplete on_display_mini_timer_autocomplete_;
    TogglDisplaySyncState on_display_sync_state_;
    TogglDisplayUnsyncedItems on_display_unsynced_items_;
    TogglDisplayUpdate on_display_update_;
    TogglDisplayUpdateDownloadState on_display_update_download_state_;
    TogglDisplayAutotrackerRules on_display_autotracker_rules_;
    TogglDisplayAutotrackerNotification on_display_autotracker_notification_;
    TogglDisplayPromotion on_display_promotion_;

    // Cached views
    Poco::Int64 lastSyncState;
    Poco::Int64 lastUnsyncedItemsCount;
    bool lastDisplayLoginOpen;
    uint64_t lastDisplayLoginUserID;
    Poco::Int64 lastOnlineState;
    error lastErr;

    Poco::Logger &logger() const;
};

TogglTimeEntryView *timeEntryViewItem(
    const RelatedData &related,
    const TimeEntry *te,
    const Poco::Int64 total_duration_for_date);

}  // namespace toggl

#endif  // SRC_GUI_H_
