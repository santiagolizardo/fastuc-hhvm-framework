<?hh // strict
namespace Fastuc\Utils;

/**
 * Generates a queue for RabbitMQ
 */
Class QueueProducer
{
	/**
	 * @var string
	 */
	private string $queueName;

	/**
	 * @var string
	 */
	private string $exchangeName;

	/**
	 * @param string $queueName
	 * @param string $exchangeName
	 */
	public function __construct( string $queueName, string $exchangeName )
	{
		$this->queueName = $queueName;
		$this->exchangeName = $exchangeName;
	}

	/**
	 * @return string
	 */
	public function getQueueName() : string
	{
		return $this->queueName;
	}

	/**
	 * @return string
	 */
	public function getExchangeName() : string
	{
		return $this->exchangeName;
	}

	/**
	 * @param string $source
	 */
	public function enqueue( string $source )
	{
		$serializedMessage = serialize( $source );
		
		$queueConfigFile = new \Fastuc\Config\File( 'mq' );
		$queueConfig = $queueConfigFile->getValue();
		
		$conn = new \PhpAmqpLib\Connection\AMQPConnection( $queueConfig['host'], $queueConfig['port'], $queueConfig['user'], $queueConfig['pass'], $queueConfig['path'] );
		
		$ch = $conn->channel();
		
		$ch->exchange_declare( $this->exchangeName, 'direct', false, true, false );
		
		$ch->queue_declare( $this->queueName, false, true, false, false);
		$ch->queue_bind( $this->queueName, $this->exchangeName );
		
		$task = new \PhpAmqpLib\Message\AMQPMessage(
				$serializedMessage,
				array( 'content_type' => 'text/plain', 'delivery_mode' => 2 )
		);
		$ch->basic_publish( $task, $this->exchangeName );
		
		$ch->close();
		$conn->close();
	}
}

