<?hh // strict
namespace Fastuc\Email;

/**
 * This class encapsulates the sending of emails using default system SMTP server.
 */
class Message 
{
	/**
	 * @var string
	 */
	private string $subject;

	/**
	 * @var string
	 */
	private string $body;

	/**
	 * @var string
	 */
	private string $from;

	/**
	 * @var string
	 */
	private string $replyTo;

	/**
	 * @var array
	 */
	private array $recipients;

	public function __construct()
	{
		$this->from = $this->replyTo = null;
		$this->subject = $this->body = null;
		$this->recipients = array();
	}

	/**
	 * @param string $subject
	 * @return $this
	 */
	public function setSubject( string $subject ) : this
	{
		$this->subject = $subject;
		return $this;
	}

	/**
	 * @return string
	 */
	public function getSubject() : string
	{
		return $this->subject;
	}

	/**
	 * @param string $body
	 * @return $this
	 */
	public function setBody( string $body ) : this
	{
		$this->body = $body;
		return $this;
	}

	/**
	 * @return string
	 */
	public function getBody() : string
	{
		return $this->body;
	}

	/**
	 * @param string $address
	 * @param string $name
	 * @return $this
	 */
	public function setFrom( string $address, string $name = null ) : this
	{
		$this->from = Utils::formatAddress( $address, $name );
		return $this;
	}

	/**
	 * @return string
	 */
	public function getFrom() : string
	{
		return $this->from;
	}

	/**
	 * @param string $address
	 * @param string $name
	 * @return $this
	 */
	public function setReplyTo( string $address, string $name = null ) : this
	{
		$this->replyTo = Utils::formatAddress( $address, $name );
		return $this;
	}

	/**
	 * @return string
	 */
	public function getReplyTo() : string
	{
		return $this->replyTo;
	}

	/**
	 * @param string $address
	 * @param string $name
	 * @return $this
	 */
	public function setTo( string $address, string $name = null ) : this
	{
		$this->addRecipient( $address, $name );
		return $this;
	}

	/**
	 * @param string $address
	 * @param string $name
	 * @return $this
	 */
	public function addRecipient( string $address, string $name = null ) : this
	{
		$this->recipients[] = Utils::formatAddress( $address, $name );
		return $this;
	}

	/**
	 * @return array
	 */
	public function getRecipients() : array
	{
		return $this->recipients;
	}

	/**
	 * @throws \Fastuc\Email\Exception
	 */
	public function send() : void
	{
		$headers = array();
		$headers[] = 'From: ' . $this->from;

		if( null !== $this->replyTo )
		{
			$headers[] = 'Reply-To: ' . $this->replyTo;
		}

		$headers[] = 'X-Mailer: PHP/' . phpversion();

		if( false === mail( implode( ';', $this->recipients ), $this->subject, $this->body, implode( "\r\n", $headers ) ) )
		{
			throw new Exception( 'The email message could not be sent' );
		}
	}
}

