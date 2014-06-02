<?hh // strict
namespace Fastuc;

/**
 * Stores and retrieves volatile messages (aka FlashMessages) with feedback information.
 */
class FlashMessages
{
	private Vector<array> $messages;

	public function __construct()
	{
		$this->messages = new Vector<array>();
	}

	/**
	 * @param string $message
	 * @param string $type
	 */
	public function addMessage( string $message, string $type = 'info' ) : void
	{
		$this->messages->add( array(
			'type' => $type,
			'label' => $message
		) );
	}

	/**
	 * @param string $message
	 */
	public function addErrorMessage( string $message ) : void
	{
		$this->addMessage( $message, 'error' );
	}

	/**
	 * @return array
	 */
	public function getMessages() : Vector<array>
	{
		return $this->messages;
	}
}

