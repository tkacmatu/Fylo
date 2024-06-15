#include <iostream>
#include <memory>

class FileOperation {
public:
    virtual void execute() = 0;
    virtual std::shared_ptr<FileOperation> clone() const = 0;
};

class CCreate : public FileOperation {
public:
    void execute() override {
        std::cout << "Performing Create operation." << std::endl;
    }

    std::shared_ptr<FileOperation> clone() const override {
        return std::make_shared<CCreate>(*this);
    }
};

class File {
public:
    virtual std::shared_ptr<File> clone() const = 0;
    virtual void performOperation(const std::shared_ptr<FileOperation>& operation) = 0;
};

class BinaryFile : public File {
public:
    std::shared_ptr<File> clone() const override {
        return std::make_shared<BinaryFile>(*this);
    }

    void performOperation(const std::shared_ptr<FileOperation>& operation) override {
        operation->execute();
        std::cout << "Performing BinaryFile-specific operation." << std::endl;
    }
};

class TextFile : public File {
public:
    std::shared_ptr<File> clone() const override {
        return std::make_shared<TextFile>(*this);
    }

    void performOperation(const std::shared_ptr<FileOperation>& operation) override {
        operation->execute();
        std::cout << "Performing TextFile-specific operation." << std::endl;
    }
};

class Folder : public File {
public:
    std::shared_ptr<File> clone() const override {
        return std::make_shared<Folder>(*this);
    }

    void performOperation(const std::shared_ptr<FileOperation>& operation) override {
        operation->execute();
        std::cout << "Performing Folder-specific operation." << std::endl;
    }
};

class SymbolicLink : public File {
public:
    std::shared_ptr<File> clone() const override {
        return std::make_shared<SymbolicLink>(*this);
    }

    void performOperation(const std::shared_ptr<FileOperation>& operation) override {
        operation->execute();
        std::cout << "Performing SymbolicLink-specific operation." << std::endl;
    }
};

int main() {
    std::shared_ptr<File> binaryFile = std::make_shared<BinaryFile>();
    std::shared_ptr<File> textFile = std::make_shared<TextFile>();
    std::shared_ptr<File> folder = std::make_shared<Folder>();
    std::shared_ptr<File> symbolicLink = std::make_shared<SymbolicLink>();

    std::shared_ptr<FileOperation> createOperation = std::make_shared<CCreate>();

    binaryFile->performOperation(createOperation);
    textFile->performOperation(createOperation);
    folder->performOperation(createOperation);
    symbolicLink->performOperation(createOperation);

    return 0;
}
