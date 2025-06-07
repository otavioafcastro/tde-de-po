public class Produto
{
//Em cada classe criada aonde foi necessário usei Encapsulamento, para os dados serem protegidos e acessados só onde é necessário. Nas 4 linhas abaixos é um exemplo.
    public string Id { get; }
    public string Nome { get; }
    public double Preco { get; set; }
    public string Categoria { get; }

    public Produto(string id, string nome, double preco, string categoria) //Aqui é um exemplo de construtor que garante que um produto só será criado com dados completos.
  
//Abaixo está a validação obrigatória de produto. Evita cadastro com preço inválido.Mostrando responsabilidade única SRP.
        {
        if (preco <= 0)
        {
            Console.WriteLine("Preço inválido");
            return;
        }

        Id = id;
        Nome = nome;
        Preco = preco;
        Categoria = categoria;
    }
}

public class Cliente
{
    public int Id { get; private set; }
    public string Nome { get; private set; }
    public string Email { get; private set; }
    public string Cpf { get; private set; }

    public Cliente(int id, string nome, string email, string cpf)
    {
        Id = id;
        Nome = nome;
        Email = email;
        Cpf = cpf;
    }
}

public class ItemPedido // Representa um item dentro de um pedido.
{
    public Produto Produto { get; private set; }
    public int Quantidade { get; private set; }

    public ItemPedido(Produto produto, int quantidade)
    {
        Produto = produto;
        Quantidade = quantidade;
    }

    public double Subtotal() //Isola uma responsabilidade SRP, ajuda a manter o código limpo Clean Code.

    {
        return Produto.Preco * Quantidade;
    }
}

public interface IDesconto //Define um contrato para qualquer tipo de desconto. Aplica o Princípio Aberto/Fechado OCP, da pra criar novos tipos de desconto sem mudar a lógica do pedido.
{
    double AplicarDesconto(double total);
}

public class DescontoFixoPorQuantidade : IDesconto  // Aplica Polimorfismo (usa a interface para comportamentos diferentes).
{
    private List<ItemPedido> itens; //Recebe os itens para calcular o desconto com base na quantidade total.
    public DescontoFixoPorQuantidade(List<ItemPedido> itens)
    {
        this.itens = itens;
    }

    public double AplicarDesconto(double total) //Aqui criei um desconto de R$50 se tiver 10 ou mais itens como foi pedido na prova.
    {
        int totalItens = 0;

        foreach (var item in itens)
        {
            totalItens += item.Quantidade;
        }

        if (totalItens >= 10)
        {
            return total - 50;
        }

        return total;
    }
}

public class Pedido
{
    public int Id { get; private set; }
    public Cliente Cliente { get; private set; }
    public List<ItemPedido> Itens { get; private set; }
    public DateTime Data { get; private set; }

    public Pedido(int id, Cliente cliente)
    {
        Id = id;
        Cliente = cliente;
        Itens = new List<ItemPedido>();
        Data = DateTime.Now;
    }

    public void AdicionarItem(ItemPedido item)
    {
        Itens.Add(item);
    }

    public double CalcularTotal(IDesconto desconto)
    {
        double total = 0;

        foreach (var item in Itens)
        {
            total += item.Subtotal();
        }

        return desconto.AplicarDesconto(total);
    }
}

public class PedidoRepositorio //Mantive a ideia do Commit anterior pra simular um banco de dados armazenando na memória. Isso aplica o Design Pattern Repository
{
    private List<Pedido> pedidos = new List<Pedido>(); //A lista armazena os pedidos salvos.

    public void Salvar(Pedido pedido) //Adiciona o pedido à lista SRP: a classe só gerencia pedidos.
    {
        pedidos.Add(pedido);
        Console.WriteLine("Pedido salvo com sucesso.");
    }

    public void ListarTodos() //Mostra todos os pedidos feitos.
    {
        foreach (var pedido in pedidos)
        {
            Console.WriteLine("Pedido ID: " + pedido.Id + ", Cliente: " + pedido.Cliente.Nome + ", Data: " + pedido.Data);
        }
    }
}

public class PedidoFactory //Eu criei essa classe PedidoFactory só pra deixar a parte de criar pedidos separada da lógica do pedido em si. Achei que assim o código ficava mais organizado e limpo. Eu vi que isso se chama padrão Factory, mas fiz do meu jeito, uma forma mais simples.
{
    public Pedido CriarPedido(int id, Cliente cliente)
    {
        return new Pedido(id, cliente);
    }
}
class Program
{
    static void Main(string[] args)
    {
        var cliente = new Cliente(1, "Guilherme", "profgui@unifeb.com", "123.456.789-00");

        var produto1 = new Produto("P001", "Mouse", 150.00, "Periféricos");
        var produto2 = new Produto("P002", "Teclado", 200.00, "Periféricos");

        var item1 = new ItemPedido(produto1, 5);
        var item2 = new ItemPedido(produto2, 6);

        var factory = new PedidoFactory();
        var pedido = factory.CriarPedido(1001, cliente);

        pedido.AdicionarItem(item1);
        pedido.AdicionarItem(item2);

        var desconto = new DescontoFixoPorQuantidade(pedido.Itens);
        var total = pedido.CalcularTotal(desconto);

        Console.WriteLine($"Total com desconto: R$ {total}");

        var repositorio = new PedidoRepositorio();
        repositorio.Salvar(pedido);
        repositorio.ListarTodos();
    }
}

