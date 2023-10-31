#include <iostream>
#include <opencv2/opencv.hpp>

int main() {
    // Carregue o classificador Haar Cascade para detecção de faces
    cv::CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
        std::cerr << "Erro ao carregar o classificador Haar Cascade." << std::endl;
        return -1;
    }

    // Inicialize a câmera ou carregue uma imagem
    cv::VideoCapture cap(0);  // Use 0 para a câmera padrão ou forneça o caminho para um arquivo de imagem

    if (!cap.isOpened()) {
        std::cerr << "Erro ao abrir a câmera ou o arquivo de imagem." << std::endl;
        return -1;
    }

    cv::Mat frame;

    while (true) {
        cap >> frame;  // Captura um quadro da câmera ou do arquivo de imagem

        if (frame.empty()) {
            std::cerr << "Quadro vazio." << std::endl;
            break;
        }

        // Converta o quadro para escala de cinza
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);

        // Detecte rostos no quadro
        std::vector<cv::Rect> faces;
        face_cascade.detectMultiScale(gray, faces, 1.3, 5);

        // Desenhe retângulos ao redor dos rostos detectados
        for (const auto& face : faces) {
            cv::rectangle(frame, face, cv::Scalar(0, 255, 0), 2);
        }

        cv::flip(frame, frame, 1);

        // Exiba o quadro com os rostos detectados
        cv::imshow("Detecção de Rosto", frame);

        if (cv::waitKey(10) == 27) {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();

    return 0;
}