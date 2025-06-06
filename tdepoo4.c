public class Produto 
{
    public string Id { get; }
    public string Nome { get; }
    public double Preco { get; set; }
    public string Categoria { get; }

    public Produto(string id, string nome, double preco, string categoria)
    {
        if (preco <= 0)
        Console.WriteLine("Preço inválido");
        return;
        Id = id;
        Nome = nome;
        Preco = preco;
        Categoria = categoria;
    }
}
public class Cliente {
    public int Id { get; private set; }
    public string Nome { get; private set; }
    public string Email { get; private set; }
    public string Cpf { get; private set; }

    public Cliente(int id, string nome, string email, string cpf) {
        Id = id;
        Nome = nome;
        Email = email;
        Cpf = cpf;
    }
}
public class ItemPedido {
    public Produto Produto { get; private set; }
    public int Quantidade { get; private set; }

    public ItemPedido(Produto produto, int quantidade) {
        Produto = produto;
        Quantidade = quantidade;
    }
      //Abaixo seria um metódo da classe Item pedido na qual seu objetivo é multiplicar o preço pela quantidade, dando o subtotal do item, por exemplo: Cliente comprou dois mouses no valor de 150 reais, ele irá entender da seguinte forma ( 150 * 2 ) e irá retornar o subtotal. 
    
    public decimal Subtotal() {
        return Produto.Preco * Quantidade;
    }
}
//Interface seria um modelo que define um contrato, toda classe que seguir ele deve implementar o metódo aplicar desconto.
public interface IDesconto {
    decimal AplicarDesconto(decimal total);
}
public class DescontoFixoPorQuantidade : IDesconto {
    public decimal AplicarDesconto(decimal total, List<ItemPedido> itens) {
        int totalItens = itens.Sum(i => i.Quantidade);
        if (totalItens >= 10) {
            return total - 50; // Crei uma regra de desconto de R$50 se o cliente estiver comprando 10 ou mais itens.
        }
        return total;
    }
}

public class Pedido {
    public int Id { get; private set; }
    public Cliente Cliente { get; private set; }
    public List<ItemPedido> Itens { get; private set; }
    public DateTime Data { get; private set; }

    public Pedido(int id, Cliente cliente) {
        Id = id;
        Cliente = cliente;
        Itens = new List<ItemPedido>();//Cria uma lista vazia de itens para que depois seja possivel adicionar itens.
        Data = DateTime.Now; // Armazena a data e hora atual no momento em que o pedido foi criado.
    }

    public void AdicionarItem(ItemPedido item) {
        Itens.Add(item);
    }
// Itens.Sum(i => i.Subtotal()); soma o valor de todos os produtos com base na quantidade. 
    public decimal CalcularTotal(IDesconto desconto) {
        decimal total = Itens.Sum(i => i.Subtotal());
        return desconto.AplicarDesconto(total); // Retorna o total com ou sem desconto.
    }
}

public class PedidoRepositorio {
    private List<Pedido> pedidos = new List<Pedido>(); // Cria uma lista privada de pedidos, que só é acessada dentro da própria classe. Pesquisei um pouco e achei interessante fazer dessa forma pra simular um banco de dados.
     //Abaixo salva e armazena o pedido 
    public void Salvar(Pedido pedido) {
        pedidos.Add(pedido);
        Console.WriteLine("Pedido salvo com sucesso.");
    }
}
