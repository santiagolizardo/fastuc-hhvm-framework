<?hh // strict
namespace Fastuc\Email;

class MessageTest extends \PHPUnit_Framework_TestCase
{
	public function setUp()
	{
		$this->message = new Message;
	}

	public function testInitialization()
	{
		$this->assertNull( $this->message->getSubject() );
		$this->assertEquals( array(), $this->message->getRecipients() );
	}

	public function testFluentInterface()
	{
		$this->assertSame( $this->message, $this->message->setFrom( 'from@foo.bar' ) );
		$this->assertSame( $this->message, $this->message->addRecipient( 'from@foo.bar' ) );
		$this->assertSame( $this->message, $this->message->setSubject( 'Hello moto' ) );
		$this->assertSame( $this->message, $this->message->setBody( 'Cheers' ) );
	}

	public function testFrom()
	{
		$this->assertNull( $this->message->getFrom() );

		$this->message->setFrom( 'foo@bar.net' );
		$this->assertEquals( 'foo@bar.net', $this->message->getFrom() );
		
		$this->assertNull( $this->message->getReplyTo() );
		$this->message->setReplyTo( $this->message->getFrom() );
		$this->assertEquals( 'foo@bar.net', $this->message->getReplyTo() );

		$this->message->setFrom( 'foo@bar.net', 'Mr. Foo Bar' );
		$this->assertEquals( 'Mr. Foo Bar <foo@bar.net>', $this->message->getFrom() );
	}
}

