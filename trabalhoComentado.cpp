//Incluindo bibliotecas:
#include <iostream>
#include <vector> // Para usar vetores
#include <cmath> // Para usar funções trigonométricas
#include <algorithm> // Retorna true se cada elemento do intervalo classificado [first2, last2) for encontrado dentro do intervalo classificado [first1, last1)
#include <locale.h> // Para a exibição de caracteres especiais (ç, acentuação, etc)
#include <clocale> 

using namespace std;


//Definição de tipos:
typedef vector<int> Vector; // Representa um vetor de inteiros
typedef vector<Vector> Matrix; // Representa uma matriz de inteiros


//Inicialização dos dados:
//Matriz que representa os padrões de entrada,  onde cada linha é um vetor de inteiros que representa um padrão
Matrix entradas = {{1, 1, 1, -1},
                   {-1, -1, 1, -1},
                   {-1, -1, -1, -1},
                   {1, -1, -1, 1},
                   {-1, 1, -1, -1},
                   {1, -1, 1, 1},
                   {1, 1, 1, 1},
                   {-1, -1, -1, 1},
                   {-1, 1, 1, -1},
                   {1, 1, -1, 1}};

//Vetor de strings que contém os nomes associados a cada padrão de entrada.
vector<string> rostos = {"Rosto 1", "Rosto 2", "Rosto 3", "Rosto 4", "Rosto 5",
                         "Rosto 6", "Rosto 7", "Rosto 8", "Rosto 9", "Rosto 10"};

Matrix pesos;


//Funções:

//Função aprendizagemHebbiana():
//Implementa o algoritmo de aprendizado Hebbiano, que atualiza os pesos da matriz pesos com base nas entradas fornecidas
void aprendizagemHebbiana() {
    for (const auto& entrada : entradas) {
        Matrix outerProduct;
        for (const auto& x : entrada) {
            Vector row;
            for (const auto& y : entrada) {
                row.push_back(x * y); /* A função push_back é usada para adicionar o resultado da multiplicação (x * y) ao vetor row.
                                        Posteriormente, o vetor row completo é adicionado ao final da matriz outerProduct usando novamente o push_back.
                                        Essa função é útil quando você deseja adicionar elementos dinamicamente em um contêiner sequencial, expandindo-o
                                        conforme necessário*/
            }
            outerProduct.push_back(row);
        }

        //Para cada padrão de entrada, a função calcula o produto externo do vetor de entrada consigo mesmo e atualiza os pesos somando o produto externo à matriz de pesos
        for (size_t i = 0; i < pesos.size(); ++i) {
            for (size_t j = 0; j < pesos[i].size(); ++j) {
                pesos[i][j] += outerProduct[i][j];
            }
        }
    }
}


//Função calcularCirculoCosseno()
/*Para cada padrão de entrada, a função calcula o produto escalar entre o vetor de entrada fornecido e o padrão de entrada, bem como as normas dos dois vetores.
 Dito isso, "Círculo do cosseno" é uma medida que indica quantos padrões de entrada têm uma similaridade de cosseno alta em relação ao vetor de entrada */
double calcularCirculoCosseno(const Vector& vetor) { 
    double circuloCosseno = 0.0;

    //Loop para percorrer cada padrão de entrada da matriz entradas
    for (const auto& entrada : entradas) {  
        
        //Variáveis usadas para calcular o produto escalar e as normas dos vetores
        double dotProduct = 0.0;
        double normA = 0.0;
        double normB = 0.0;
        
        // Loop para calcular o produto escalar entre o vetor de entrada fornecido e o padrão de entrada atual, bem como as normas dos dois vetores
        /* Ele percorre os elementos dos vetores entrada e vetor, multiplicando os elementos 
        correspondentes e somando os resultados às variáveis apropriadas */
        for (size_t i = 0; i < entrada.size(); ++i) { 
            dotProduct += entrada[i] * vetor[i];
            normA += entrada[i] * entrada[i];
            normB += vetor[i] * vetor[i];
        }

        //Calcula a similaridade de cosseno entre os vetores e conta quantos padrões de entrada têm uma similaridade de cosseno maior ou igual a 0.9
        double cosineSimilarity = dotProduct / (sqrt(normA) * sqrt(normB));
        if (cosineSimilarity >= 0.9) {
            circuloCosseno++;
        }
    }
    //Após percorrer todos os padrões de entrada, retornamos o valor de circuloCosseno
    return circuloCosseno;
}


//Função imprimirMatriz():
//Imprime uma matriz na saída padrão, juntamente com um título fornecido como parâmetro
void imprimirMatriz(const Matrix& matriz, const string& titulo) {
    cout << titulo << "\n";
    for (const auto& row : matriz) {
        for (const auto& value : row) {
            cout << value << " ";
        }
        cout << "\n";
    }
}


//Função Principal
int main() {

/*Comando para que as configurações regionais sejam definidas para o idioma português,
  e que deve ser aplicada em todos os aspectos do programa. É uma função da biblioteca <clocale>*/
setlocale(LC_ALL, "Portuguese");


    //Inicialização dos pesos
    pesos = Matrix(entradas[0].size(), Vector(entradas[0].size(), 0));

    //Chama a função de aprendizagem hebbiana
    aprendizagemHebbiana();

    //Menu de opções para interação com o usuário
    while (true) {
        cout << "\n====== MENU ======\n";
        cout << "1. Imprimir matriz referente a um rosto\n";
        cout << "2. Imprimir matriz com os rostos armazenados\n";
        cout << "3. Imprimir matriz após lembrança dos rostos\n";
        cout << "4. Imprimir quantidade de vetores responsáveis pelo círculo do cosseno\n";
        cout << "5. Mostrar quantidade de respostas da rede neural para cada rosto aprendido\n";
        cout << "0. Encerrar programa\n";

        int escolha;
        cout << "Escolha uma opção: ";
        cin >> escolha;

        //Dependendo da opção selecionada pelo usuário, o código executa as respectivas ações.
        switch (escolha) {

            case 1: {
                int rosto;
                cout << "Digite o número do rosto: ";
                cin >> rosto;
                imprimirMatriz({entradas[rosto - 1]}, rostos[rosto - 1]);
                break;
            }

            case 2:
                imprimirMatriz(entradas, "Matriz com os rostos armazenados:");
                break;

            case 3:
                imprimirMatriz(pesos, "Matriz após lembrança dos rostos:");
                break;

            case 4: {
                //Vetor criado para armazenar os valores que serão inseridos pelo usuário
                Vector vetor;   
                cout << "Digite o vetor (ex: 1 1 1 -1): ";
                
                for (size_t i = 0; i < entradas[0].size(); ++i) { /*Loop executado para ler os valores digitados pelo usuário. Ele percorre cada posição do vetor entrada[0] 
                                                                    (que é uma das linhas da matriz entradas) usando o tamanho desse vetor como limite superior. */
                    int valor;
                    cin >> valor;
                    vetor.push_back(valor); //O valor lido é adicionado ao final do vetor vetor usando o método push_back
                }

                //A função calcularCirculoCosseno(vetor) é chamada:
                double circuloCosseno = calcularCirculoCosseno(vetor); //O valor retornado pela função calcularCirculoCosseno é armazenado na variável circuloCosseno
                cout << "A quantidade de vetores responsáveis pelo círculo do cosseno é: " << circuloCosseno << "\n";
                break;
            }


            case 5:
                for (size_t i = 0; i < entradas.size(); ++i) { /*Loop para percorrer cada elemento da matriz 'entradas'. 
                                                                Cada elemento representa um rosto aprendido pela rede neural.*/
                    Vector resultado; //Vetor para armazenar os resultados da multiplicação entre o vetor de entrada e a matriz de pesos
                    
                    for (size_t j = 0; j < pesos.size(); ++j) {  /*Loop para percorrer os elementos da matriz de pesos
                                                                    Cada elemento representa um peso associado a uma conexão sináptica na rede neural*/
                        double soma = 0.0; //Variável para acumular a soma ponderada entre os elementos do vetor de entrada e os pesos correspondentes.
                        
                        for (size_t k = 0; k < pesos[j].size(); ++k) { //Loop para percorrer os elementos de cada linha da matriz de entrada e cada coluna da matriz de pesos
                            soma += entradas[i][k] * pesos[k][j]; //Adiciona-se a multiplicação entre os elementos correspondentes na variável soma
                        }

                        resultado.push_back(soma); //O resultado da soma é adicionado ao vetor resultado usando o método push_back
                    }

                    //A função max_element é chamada para encontrar o maior elemento no vetor resultado. O resultado é armazenado em maxElement, que é um iterador apontando para o elemento máximo.
                    auto maxElement = max_element(resultado.begin(), resultado.end());

                    //A função distance é usada para obter a distância (ou índice) entre o início do vetor resultado e o iterador maxElement. Isso nos dá o índice do elemento máximo no vetor
                    size_t indice = distance(resultado.begin(), maxElement);

                    //O programa imprime o resultado da rede neural para cada rosto aprendido
                    cout << "Rosto " << i + 1 << " - " << rostos[indice] << "\n";

                    //O loop externo continua, percorrendo todos os rostos aprendidos na matriz entradas.
                }
                break;


            //Quando a opção de encerrar o programa é acionada:
            case 0:
                return 0;
            
            
            //Quando o valor da variável escolha não corresponde a nenhum dos casos acima:
            default:
                cout << "Opção inválida! Por favor, escolha uma opção válida.\n";
        }
    }
}
