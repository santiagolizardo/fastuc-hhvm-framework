<?hh // strict
namespace Fastuc\Utils;

class QueueProducerTest extends \PHPUnit_Framework_TestCase
{
	public function testQueue()
	{
		$queueProducer = new QueueProducer( 'TWITTER_QUEUE', 'TWITTER_DISPATCHER');
		
		$this->assertEquals( 'TWITTER_QUEUE', $queueProducer->getQueueName() );
		$this->assertEquals( 'TWITTER_DISPATCHER', $queueProducer->getExchangeName() );
	}
}
