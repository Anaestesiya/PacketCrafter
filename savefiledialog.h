#ifndef SAVEFILEDIALOG_H
#define SAVEFILEDIALOG_H

#include <QFileDialog>
#include <QMessageBox>
#include <QDialog>
#include <QVBoxLayout>
#include <QRadioButton>
#include <QPushButton>

class SaveFileDialog : public QDialog
{
    Q_OBJECT

public:
    SaveFileDialog(QWidget *parent = nullptr) : QDialog(parent)
    {
        setWindowTitle("Save File");

        // Create radio buttons for format selection
        QRadioButton *textRadio = new QRadioButton("Text Format");
        QRadioButton *binaryRadio = new QRadioButton("Binary Format");
        textRadio->setChecked(true);

        // Create OK and Cancel buttons
        QPushButton *okButton = new QPushButton("OK");
        QPushButton *cancelButton = new QPushButton("Cancel");

        // Connect signals and slots
        connect(okButton, &QPushButton::clicked, this, &SaveFileDialog::onOkClicked);
        connect(cancelButton, &QPushButton::clicked, this, &SaveFileDialog::reject);

        // Create layout and add widgets
        QVBoxLayout *layout = new QVBoxLayout;
        layout->addWidget(textRadio);
        layout->addWidget(binaryRadio);
        layout->addWidget(okButton);
        layout->addWidget(cancelButton);

        setLayout(layout);

        // Store pointers to radio buttons for later use
        m_textRadio = textRadio;
        m_binaryRadio = binaryRadio;
    }

signals:
    void saveFile(const QString& filePath, bool isBinaryFormat);

private slots:
    void onOkClicked()
    {
        // Open file dialog to choose path
        QString filePath = QFileDialog::getSaveFileName(this, "Save File", "", "All Files (*.*)");
        if (!filePath.isEmpty())
        {
            // Emit saveFile signal with chosen path and format
            emit saveFile(filePath, m_binaryRadio->isChecked());
        }
        else
        {
            QMessageBox::warning(this, "Error", "No file path selected.");
        }
        accept();
    }

private:
    QRadioButton *m_textRadio;
    QRadioButton *m_binaryRadio;
};

#endif // SAVEFILEDIALOG_H
