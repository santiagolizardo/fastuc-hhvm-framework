<?hh // strict
namespace Fastuc;

/**
 * Stores and retrieves volatile messages (aka FlashMessages) with feedback information.
 */
class FlashMessages
{
	/**
	 * @var array
	 */
	private array $messages;

	/**
	 * Class constructor.
	 */
	public function __construct()
	{
		$this->messages = array();
	}

	/**
	 * @param string $message
	 * @param string $type
	 */
	public function addMessage( string $message, string $type = 'info' ) : void
	{
		$this->messages[] = array(
			'type' => $type,
			'label' => $message
		);
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
	public function getMessages() : array
	{
		return $this->messages;
	}
}

