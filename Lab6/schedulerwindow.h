#ifndef SCHEDULERWINDOW_H
#define SCHEDULERWINDOW_H

#include <QMainWindow>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QPushButton>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QSpinBox>
#include <QComboBox>
#include <QTextEdit>
#include <QGroupBox>
#include <QScrollArea>
#include <QTimer>
#include <QProgressBar>
#include <QFrame>
#include <QPainter>
#include <QMessageBox>
#include "schedulingcore.h"

class SchedulerWindow : public QMainWindow
{
    Q_OBJECT

public:
    SchedulerWindow(QWidget *parent = nullptr);
    ~SchedulerWindow();

private slots:
    void addProcess();
    void removeProcess();
    void clearProcesses();
    void runSimulation();
    void onAlgorithmChanged();
    void showNextStep();
    void showPreviousStep();
    void resetAnimation();
    void playAnimation();
    void pauseAnimation();

private:
    void setupUI();
    void setupProcessInputArea();
    void setupControlArea();
    void setupResultsArea();
    void setupVisualizationArea();
    void updateProcessTable();
    void updateResultsTable();
    void updateExecutionLog();
    void updateVisualization();
    void updateGanttChart();
    void animateExecution();
    void drawProcessBlock(QPainter& painter, int startTime, int endTime, int processId, const QStringList& colors, int /* chartHeight */);
    void drawExecutionBlocks(QPainter& painter, int axisY);
    void drawGanttBlock(QPainter& painter, int startTime, int endTime, int processId, const QStringList& colors, int axisY, bool showEndTime = false);
    void drawIdleBlock(QPainter& painter, int startTime, int endTime, int axisY);
    void drawQueueVisualization(QPainter& painter, int axisY);
    void updateAnimationHighlight();
    std::vector<int> getQueueStateAtStep(int step);
    int getCurrentRunningProcess(int step);
    
    // UI Components
    QWidget *centralWidget;
    QVBoxLayout *mainLayout;
    
    // Process Input Area
    QGroupBox *inputGroup;
    QTableWidget *processTable;
    QPushButton *addProcessBtn;
    QPushButton *removeProcessBtn;
    QPushButton *clearProcessesBtn;
    
    // Control Area
    QGroupBox *controlGroup;
    QComboBox *algorithmCombo;
    QSpinBox *quantumSpin;
    QLabel *quantumLabel;
    QPushButton *runBtn;
    QPushButton *resetBtn;
    
    // Results Area
    QGroupBox *resultsGroup;
    QTableWidget *resultsTable;
    QLabel *avgWaitingLabel;
    QLabel *avgTurnaroundLabel;
    
    // Visualization Area
    QGroupBox *visualGroup;
    QFrame *ganttChart;
    QScrollArea *ganttScrollArea;
    
    // Animation Controls
    QGroupBox *animationGroup;
    QPushButton *playBtn;
    QPushButton *pauseBtn;
    QPushButton *stepForwardBtn;
    QPushButton *stepBackwardBtn;
    QPushButton *resetAnimationBtn;
    QProgressBar *animationProgress;
    QTimer *animationTimer;
    
    // Data
    CPUScheduler scheduler;
    std::vector<Process> processes;
    std::vector<ExecutionStep> executionSteps;
    int currentStep;
    bool isAnimating;
    
    // Constants
    static const int PROCESS_HEIGHT = 30;
    static const int TIME_UNIT_WIDTH = 40;
};

#endif // SCHEDULERWINDOW_H